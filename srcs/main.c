/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:31:26 by kaheinz           #+#    #+#             */
/*   Updated: 2022/10/19 12:09:38 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	skip_space(char *command)
{
	int		i;

	i = 0;
	while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'))
		i++;
	if (command[i] == '\0')
		return (1);
	return (0);
}

void	shell(char *command, t_ms *ms)
{
	if (skip_space(command) == 0)
	{
		add_history(command);
		tokenice(command, ms);
		printing_tokens(ms->tokenlist);
		if (ms->lex->error == 0)
			execution(ms);
		freeing_tokens(ms);
	}
}

t_ms	*struct_allocation(void)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	ms->pipes_struct = malloc(sizeof(t_pipes));
	ms->lex = malloc(sizeof(t_lex));
	return (ms);
}

void	closing_fd(t_ms *ms)
{
	if (ms->pipes_struct->fd_file[0] >= 0)
		close(ms->pipes_struct->fd_file[0]);
	if (ms->pipes_struct->fd_file[1] >= 0)
		close(ms->pipes_struct->fd_file[1]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command;
	t_ms	*ms;

	(void) argc;
	(void) argv;
	parent_signals();
	ms = struct_allocation();
	creating_env_list(envp, ms);
	while (1)
	{
		command = readline("ksh >> ");
		init(ms, command);
		if (command == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}			
		else if (command && *command)
			shell(command, ms);
		if (command)
			free (command);
		closing_fd(ms);
	}
	freeing_all(ms, command);
	return (0);
}
