/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/13 14:30:42 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>


int	builtins(t_ms *ms)
{
	t_ms_list	*tmp;
	size_t	len;
	int	sum;
	
	len = 0;
	tmp = ms->tokenlist;
	sum = (b_pwd(ms) + b_export(ms) + b_unset(ms) + b_echo(ms) + b_cd(ms)) + b_exit(ms);
	while(tmp)
	{
		len = ft_strlen(tmp->token);
		if (b_env(tmp->token, ms) && len < 4)
		{
			tmp = tmp->next;
			sum++;
			break;
		}
		tmp = tmp->next;
	}
	return (sum);
}

void    child_signal(int sig)
{
    if (sig == SIGQUIT)
            write(1, "Quit (core dumped)\n", 19);
	if (sig == SIGINT)
			write(1, "\b\b", 2);
}
void	child1(t_ms	*ms)
{
	char	**token_array;
	
		if (ms->pipes_struct->fd_file[0] >= 0)
		{
			close(STDIN_FILENO);
			dup2(ms->pipes_struct->fd_file[0], STDIN_FILENO);
			close(ms->pipes_struct->fd_file[0]);
			ms->pipes_struct->fd_file[0] = -1;
		}
		
		if (ms->pipes_struct->fd_file[1] >= 0)
		{
			close(STDOUT_FILENO);
			dup2(ms->pipes_struct->fd_file[1], STDOUT_FILENO);
			close(ms->pipes_struct->fd_file[1]);
			ms->pipes_struct->fd_file[1] = -1;
		}
		else if (ms->pipes_struct->pipe_ends[1] >= 0)
		{
			close(STDOUT_FILENO);
			dup2(ms->pipes_struct->pipe_ends[1], STDOUT_FILENO);
		}
		close(ms->pipes_struct->pipe_ends[0]);
		close(ms->pipes_struct->pipe_ends[1]);
		token_array = make_array_token(ms);
		execve(get_cmd_path(token_array[0], make_array_env(ms)), token_array, make_array_env(ms));
		exit (127);
}

// void	child2(t_ms	*ms)
// {
// 	char	**token_array;

// 	if (ms->pipes_struct->fd_file[2] >= 0)
// 	{
// 		close(STDIN_FILENO);
// 		dup2(ms->pipes_struct->fd_file[2], STDIN_FILENO);
// 		// close(ms->pipes_struct->fd_file[2]);
// 		ms->pipes_struct->fd_file[2] = -1;
// 	}
// 	else if (ms->pipes_struct->pipe_ends[0] >= 0)
// 	{
// 		close(STDIN_FILENO);
// 		dup2(ms->pipes_struct->pipe_ends[0], STDIN_FILENO);
// 	}
// 	if (ms->pipes_struct->fd_file[3] >= 0)
// 	{
// 		close(STDOUT_FILENO);
// 		dup2(ms->pipes_struct->fd_file[3], STDOUT_FILENO);
// 		// close(ms->pipes_struct->fd_file[3]);
// 		ms->pipes_struct->fd_file[3] = -1;
// 	}
// 	close(ms->pipes_struct->pipe_ends[0]);
// 	close(ms->pipes_struct->pipe_ends[1]);
// 	token_array = make_array_token(ms);
// 	execve(get_cmd_path(token_array[0], make_array_env(ms)), token_array, make_array_env(ms));
// 	exit (127);
// }
void	child2(t_ms	*ms)
{
	char	**token_array;
	
	if (ms->pipes_struct->fd_file[0] >= 0)
	{
		close(STDIN_FILENO);
		dup2(ms->pipes_struct->fd_file[0], STDIN_FILENO);
		// close(ms->pipes_struct->fd_file[2]);
		ms->pipes_struct->fd_file[0] = -1;
	}
	else if (ms->pipes_struct->pipe_ends[0] >= 0)
	{
		close(STDIN_FILENO);
		dup2(ms->pipes_struct->pipe_ends[0], STDIN_FILENO);
	}
	if (ms->pipes_struct->fd_file[1] >= 0)
	{
		close(STDOUT_FILENO);
		dup2(ms->pipes_struct->fd_file[1], STDOUT_FILENO);
		// close(ms->pipes_struct->fd_file[3]);
		ms->pipes_struct->fd_file[1] = -1;
	}
	close(ms->pipes_struct->pipe_ends[0]);
	close(ms->pipes_struct->pipe_ends[1]);
	token_array = make_array_token(ms);
	execve(get_cmd_path(token_array[0], make_array_env(ms)), token_array, make_array_env(ms));
	exit (127);
}

int	two_sections(t_ms	*ms)
{
	signal(SIGQUIT, child_signal);
	if (pipe(ms->pipes_struct->pipe_ends) == -1)
		return (1);
	ms->pipes_struct->child_pid[0] = fork();
	if (ms->pipes_struct->child_pid[0] == -1)
		return (1);
	if (ms->pipes_struct->child_pid[0] == 0)
		child1(ms);
	waitpid(ms->pipes_struct->child_pid[0], &ms->exit_status, WUNTRACED);
	ms->current_section++;
	redirecting(ms);
	ms->pipes_struct->child_pid[1] = fork();
	if (ms->pipes_struct->child_pid[1] == -1)
		return (1);
	if (ms->pipes_struct->child_pid[1] == 0)
		child2(ms);
	close(ms->pipes_struct->pipe_ends[0]);
	close(ms->pipes_struct->pipe_ends[1]);
	close(ms->pipes_struct->fd_file[2]);
	ms->pipes_struct->fd_file[2] = -1;
	close(ms->pipes_struct->fd_file[3]);
	ms->pipes_struct->fd_file[3] = -1;
	waitpid(ms->pipes_struct->child_pid[1], &ms->exit_status, WUNTRACED);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	childm(t_ms	*ms, int	in_pipe_fd, int out_pipe_fd)
{
	char	**token_array;

	if (ms->pipes_struct->fd_file[0] >= 0)
	{
		close(STDIN_FILENO);
		dup2(ms->pipes_struct->fd_file[0], STDIN_FILENO);
		// close(ms->pipes_struct->fd_file[2]);
		ms->pipes_struct->fd_file[0] = -1;
	}
	else if (ms->pipes_struct->pipe_ends[0] >= 0 && ms->current_section != 0)
	{
		close(STDIN_FILENO);
		dup2(in_pipe_fd, STDIN_FILENO);
	}
	if (ms->pipes_struct->fd_file[1] >= 0)
	{
		close(STDOUT_FILENO);
		dup2(ms->pipes_struct->fd_file[1], STDOUT_FILENO);
		// close(ms->pipes_struct->fd_file[3]);
		ms->pipes_struct->fd_file[1] = -1;
	}
	else if ((ms->pipes_struct->pipe_ends[1] >= 0 && ms->current_section != ms->sections))
	{
			close(STDOUT_FILENO);
			dup2(out_pipe_fd, STDOUT_FILENO);
	}
	close(ms->pipes_struct->pipe_ends[0]);
	close(ms->pipes_struct->pipe_ends[1]);
	close(ms->pipes_struct->pipe2_ends[0]);
	close(ms->pipes_struct->pipe2_ends[1]);
	token_array = make_array_token(ms);
	if (!get_cmd_path(token_array[0], make_array_env(ms)))
		exit (127);
	execve(get_cmd_path(token_array[0], make_array_env(ms)), token_array, make_array_env(ms));
	exit (127);
}

int	multi_sections(t_ms	*ms)
{
	int	in_pipe_fd;
	int	out_pipe_fd;
	
	signal(SIGQUIT, child_signal);
	if (pipe(ms->pipes_struct->pipe_ends) == -1)
		return (1);
	if (pipe(ms->pipes_struct->pipe2_ends) == -1)
		return (1);
	while (ms->current_section <= ms->sections && WEXITSTATUS(ms->exit_status) == 0)
	{
		if (ms->current_section % 2 == 0)
		{
			in_pipe_fd = ms->pipes_struct->pipe2_ends[0];
			out_pipe_fd = ms->pipes_struct->pipe_ends[1];
		}
		else
		{
			in_pipe_fd = ms->pipes_struct->pipe_ends[0];
			out_pipe_fd = ms->pipes_struct->pipe2_ends[1];
		}
		ms->pipes_struct->child_pid[0] = fork();
		if (ms->pipes_struct->child_pid[0] == -1)
			return (1);
		if (ms->pipes_struct->child_pid[0] == 0)
			childm(ms, in_pipe_fd, out_pipe_fd);
		close(ms->pipes_struct->fd_file[0]);
		ms->pipes_struct->fd_file[0] = -1;
		close(ms->pipes_struct->fd_file[1]);
		ms->pipes_struct->fd_file[1] = -1;
		close(ms->pipes_struct->fd_file[2]);
		waitpid(ms->pipes_struct->child_pid[0], &ms->exit_status, WUNTRACED);
		ms->current_section++;
		redirecting(ms);
	}
	close(ms->pipes_struct->pipe_ends[0]);
	close(ms->pipes_struct->pipe_ends[1]);
	close(ms->pipes_struct->pipe2_ends[0]);
	close(ms->pipes_struct->pipe2_ends[1]);
	return (0);
}

int	execution(t_ms	*ms)
{
	char	*cmd_path;
	char	**env_arr;
	pid_t	pid;
	
	redirecting(ms);
	if (!ms->tokenlist)
		return (0);
	if (ms->sections == 0)
	{
		if (builtins(ms) > 0)
			return (0);
		env_arr = make_array_env(ms);
		cmd_path = get_cmd_path(ms->tokenlist->token, env_arr);
		signal(SIGQUIT, child_signal);
		signal(SIGINT, child_signal);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			if (ms->pipes_struct->fd_file[0] >= 0)
			{
				close(STDIN_FILENO);
				dup2(ms->pipes_struct->fd_file[0], STDIN_FILENO);
				close(ms->pipes_struct->fd_file[0]);
				ms->pipes_struct->fd_file[0] = 0;
			}
			if (ms->pipes_struct->fd_file[1] >= 0)
			{
				close(STDOUT_FILENO);
				dup2(ms->pipes_struct->fd_file[1], STDOUT_FILENO);
				close(ms->pipes_struct->fd_file[1]);
				ms->pipes_struct->fd_file[1] = 0;
			}
			execve(cmd_path, make_array_token(ms), env_arr);
			exit (127);
		}
		waitpid(pid, &ms->exit_status, WUNTRACED);
		signal(SIGQUIT, SIG_IGN);
	}
	if (ms->sections == 1)
	{
		two_sections(ms);
	}
	if (ms->sections > 1)
	{
		multi_sections(ms);
	}
	return (0);
}


// int	exit_status(t_ms	*ms)
// {
// 	t_ms_list	*tmp;

// 	tmp = ms->tokenlist;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->token, "$?\0", 3))
// 		{
			
// 			ms->exit_status = EXIT_SUCCESS;
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
