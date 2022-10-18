/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:31:26 by kaheinz           #+#    #+#             */
/*   Updated: 2022/10/18 14:55:34 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	handler_quit(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\b\b\n", 1);
		rl_redisplay();
	}
}

void	init(t_ms	*ms, char *command)
{
	ms->pipes_struct->fd_file[0] = -1;
	ms->pipes_struct->fd_file[1] = -1;
	ms->pipes_struct->fd_file[2] = -1;
	ms->pipes_struct->fd_file[3] = -1;
	ms->pipes_struct->pipe_ends[0] = -1;
	ms->pipes_struct->pipe_ends[1] = -1;
	ms->pipes_struct->pipe2_ends[0] = -1;
	ms->pipes_struct->pipe2_ends[1] = -1;
	ms->pipes_struct->child_pid[0] = -1;
	ms->pipes_struct->child_pid[1] = -1;
    ms->lex->start = 0;
	ms->lex->i = 0;
	if (command)
    	ms->lex->length = ft_strlen(command);
    ms->lex->error = 0;
}

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

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*command;
	pid_t				pid;
	t_ms				*ms;

	(void) argc;
	(void) argv;
	pid = getpid();
	ft_printf("pid is %d\n", pid);
	ms = malloc(sizeof(t_ms));
	ms->pipes_struct = malloc(sizeof(t_pipes));
	ms->lex = malloc(sizeof(t_lex));
	creating_env_list(envp, ms);
	while (1)
	{
		sa.sa_handler = &handler_quit;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		command = readline("ksh >> ");
		init(ms, command);
		if (command == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}			
		else if (command && *command)
		{
			if (skip_space(command) == 0)
			{
				add_history(command);
				tokenice(command, ms);
				printing_tokens(ms->tokenlist);
				if (ms->lex->error == 0)
					execution(ms);
//				printing_tokens(ms->tokenlist);
				freeing_tokens(ms);
			}
		}
		if (command)
			free (command);
		if (ms->pipes_struct->fd_file[0] >= 0)
			close(ms->pipes_struct->fd_file[0]);
		if (ms->pipes_struct->fd_file[1] >= 0)
			close(ms->pipes_struct->fd_file[1]);
		// if (ms->pipes_struct->fd_file[2] >= 0)
		// 	close(ms->pipes_struct->fd_file[2]);
		// if (ms->pipes_struct->fd_file[3]>= 0)
		// 	close(ms->pipes_struct->fd_file[3]);
		// printing_tokens(ms->tokenlist);
//		freeing_tokens(ms);
	}
	freeing_all(ms);
	free(command);
	free (ms);
	return (0);
}

void	creating_env_list(char **envp, t_ms *ms)
{
	t_env	*new;

	ms->env_lst_size = 0;
	while (envp[ms->env_lst_size])
	{
		new = ft_envvnew(envp[ms->env_lst_size]);
		ft_envvadd_back(&ms->env_list, new);
		ms->env_lst_size++;
	}
}
