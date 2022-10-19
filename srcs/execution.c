/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/19 11:50:34 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	childm(t_ms	*ms, int in_pipe_fd, int out_pipe_fd)
{
	char	**token_array;

	child_infilefd(ms, in_pipe_fd);
	child_outfilefd(ms, out_pipe_fd);
	token_array = make_array_token(ms);
	if (!get_cmd_path(token_array[0], make_array_env(ms)))
		exit (127);
	execve(get_cmd_path(token_array[0], make_array_env(ms)),
		token_array, make_array_env(ms));
	exit (127);
}

int	pipesandforks(int *out_pipe_fd, int *in_pipe_fd, t_ms *ms)
{
	if (ms->current_section % 2 == 0)
	{
		if (pipe(ms->pipes_struct->pipe_ends) == -1)
			return (1);
		if (ms->pipes_struct->pipe2_ends[0] != -1)
			*in_pipe_fd = ms->pipes_struct->pipe2_ends[0];
		*out_pipe_fd = ms->pipes_struct->pipe_ends[1];
	}
	else
	{
		if (pipe(ms->pipes_struct->pipe2_ends) == -1)
			return (1);
		*in_pipe_fd = ms->pipes_struct->pipe_ends[0];
		*out_pipe_fd = ms->pipes_struct->pipe2_ends[1];
	}
	if (builtins(ms) == 0)
	{
		ms->pipes_struct->child_pid[0] = fork();
		if (ms->pipes_struct->child_pid[0] == -1)
			return (1);
		if (ms->pipes_struct->child_pid[0] == 0)
			childm(ms, *in_pipe_fd, *out_pipe_fd);
	}
	return (0);
}

int	multi_sections(t_ms	*ms)
{
	int	in_pipe_fd;
	int	out_pipe_fd;

	while (ms->current_section <= ms->sections)
	{
		if (pipesandforks(&out_pipe_fd, &in_pipe_fd, ms) == 1)
			return (1);
		close(ms->pipes_struct->fd_file[0]);
		ms->pipes_struct->fd_file[0] = -1;
		close(ms->pipes_struct->fd_file[1]);
		ms->pipes_struct->fd_file[1] = -1;
		close(ms->pipes_struct->fd_file[2]);
		redirecting(ms);
		ms->current_section++;
		waitpid(ms->pipes_struct->child_pid[0], &ms->exit_status, WUNTRACED);
		if (out_pipe_fd)
			close (out_pipe_fd);
		if (in_pipe_fd)
			close (in_pipe_fd);
	}
	return (0);
}

int	execution(t_ms	*ms)
{
	redirecting(ms);
	if (!ms->tokenlist)
		return (0);
	signal(SIGQUIT, child_signal);
	signal(SIGINT, child_signal);
	if (ms->sections >= 0)
		multi_sections(ms);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
