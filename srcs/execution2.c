/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/24 13:24:10 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	builtins(t_ms *ms)
{
	int	sum;

	sum = (b_pwd(ms) + b_export(ms) + b_unset(ms) + b_echo(ms)
			+ b_cd(ms) + b_exit(ms) + b_env(ms));
	if (sum > 0)
	{
		delete_section(ms);
		ms->pipes_struct->child_pid[0] = -1;
	}
	return (sum);
}

void	child_signal(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
	if (sig == SIGINT)
		write(1, "\b\b", 2);
}

void	child_infilefd(t_ms *ms, int in_pipe_fd)
{
	if (ms->pipes_struct->fd_file[0] >= 0)
	{
		close(STDIN_FILENO);
		dup2(ms->pipes_struct->fd_file[0], STDIN_FILENO);
		close(ms->pipes_struct->fd_file[0]);
		ms->pipes_struct->fd_file[0] = -1;
	}
	else if (ms->pipes_struct->pipe_ends[0] >= 0 && ms->current_section != 0)
	{
		close(STDIN_FILENO);
		dup2(in_pipe_fd, STDIN_FILENO);
		close(in_pipe_fd);
	}
}

void	child_outfilefd(t_ms *ms, int out_pipe_fd)
{
	if (ms->pipes_struct->fd_file[1] >= 0)
	{
		close(STDOUT_FILENO);
		dup2(ms->pipes_struct->fd_file[1], STDOUT_FILENO);
		close(ms->pipes_struct->fd_file[1]);
		ms->pipes_struct->fd_file[1] = -1;
	}
	else if ((ms->pipes_struct->pipe_ends[1] >= 0
			&& ms->current_section != ms->sections))
	{
		close(STDOUT_FILENO);
		dup2(out_pipe_fd, STDOUT_FILENO);
		close(out_pipe_fd);
	}
}
