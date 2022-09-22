/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:31:26 by kaheinz           #+#    #+#             */
/*   Updated: 2022/09/22 10:25:11 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *command;

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

int	main(int argc, char **argv, char **envp)
{
	
	struct	sigaction sa;
	pid_t	pid;
	t_ms	*ms;

	(void) argc;
	(void) argv;
	pid = getpid();
	ft_printf("pid is %d\n", pid);
	
	ms = malloc(sizeof(t_ms));
	while (1)
	{
		ms->tokenlist = ft_tokennew("something", "first", 0);
		sa.sa_handler = &handler_quit;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		command = readline("cli prompt >> ");
		if (command == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}			
		else if (command && *command)
		{
			b_exit(command);
			add_history(command);
			ms->lex = tokenice(command, ms->tokenlist, envp);
		}
		if (command)
			free (command);
		execute(ms->tokenlist, envp);
		if (ms->lex.error == 0)
		{
			// printing_tokens(ms->tokenlist);
			b_export(ms, envp);
		}
		freeing_tokens(ms->tokenlist);
		// cmd_path = get_cmd_path(command, envp);
	}
	freeing_tokens(ms->tokenlist);
	free(command);
	free (ms);
	return 0;
}
