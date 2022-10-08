/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:31:26 by kaheinz           #+#    #+#             */
/*   Updated: 2022/10/08 14:46:13 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	ms->pipes_struct = malloc(sizeof(t_pipes));
	creating_env_list(envp, ms);
	while (1)
	{
		sa.sa_handler = &handler_quit;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		command = readline("ksh >> ");
		if (command == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}			
		else if (command && *command)
		{
			b_exit(command);
			add_history(command);
			ms->lex = tokenice(command, ms, envp);
			// printing_tokens(ms->tokenlist);
			if (ms->lex->error == 0)
			{
				execution(ms);
				printing_tokens(ms->tokenlist);
			}
				
			freeing_tokens(ms);
		}
		if (command)
			free (command);
		if (ms->pipes_struct->fd_file[0])
			close(ms->pipes_struct->fd_file[0]);
		if (ms->pipes_struct->fd_file[1])
			close(ms->pipes_struct->fd_file[1]);
//		printing_tokens(ms->tokenlist);
//		freeing_tokens(ms);
	}
	freeing_all(ms);
	free(command);
	free (ms);
	return 0;
}

void	creating_env_list(char **envp, t_ms *ms)
{
	t_env	*new;

	ms->env_lst_size = 0;
	while(envp[ms->env_lst_size])
	{
		new = ft_envvnew(envp[ms->env_lst_size]);
		ft_envvadd_back(&ms->env_list, new);
		ms->env_lst_size++;
	}
}
