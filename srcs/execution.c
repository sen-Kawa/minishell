/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/11 13:37:36 by ksura            ###   ########.fr       */
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

void	signal_heredoc(int sig)
{
		if (sig == SIGINT)
				printf("signal in heredoc %i", sig);
}

void	heredoc(t_ms *ms, char	*delim)
{
	char		*hereline;
	char		*herecom;

	hereline = "";
	herecom = NULL;
	while (ft_strncmp(hereline, delim, sizeof(delim)))
	{
	//	signal(SIGINT, signal_heredoc);
		hereline = readline("> ");
		if (hereline == NULL)
		{
			ft_printf("ksh: warning: here-document delimited by end-of-file (wanted `%s')\n", delim);
			ms->exit_status = 1;
			break ;
		}
		if (!ft_strncmp(hereline, delim, sizeof(delim)))
		{
			if (hereline)
				free (hereline);
			ms->pipes_struct->fd_file[0] = open(".tmp_heredoc", O_RDONLY | O_CREAT | O_TRUNC, 0777);
			break;
		}
		if (herecom)
		{
			herecom = ft_strjoin(herecom, hereline);
			herecom = ft_strjoin(herecom, "\n");
		}
		else
			herecom = ft_strjoin(hereline, "\n");
	}
	if (herecom)
	{
		ms->pipes_struct->fd_file[0] = open(".tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (ms->pipes_struct->fd_file[0] != -1)
			ft_putstr_fd(herecom, ms->pipes_struct->fd_file[0]);
		close(ms->pipes_struct->fd_file[0]);
		ms->pipes_struct->fd_file[0] = open(".tmp_heredoc", O_RDONLY);
	}
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

void	child2(t_ms	*ms)
{
	char	**token_array;

	if (ms->pipes_struct->fd_file[2] >= 0)
	{
		close(STDIN_FILENO);
		dup2(ms->pipes_struct->fd_file[2], STDIN_FILENO);
		// close(ms->pipes_struct->fd_file[2]);
		ms->pipes_struct->fd_file[2] = -1;
	}
	else if (ms->pipes_struct->pipe_ends[0] >= 0)
	{
		close(STDIN_FILENO);
		dup2(ms->pipes_struct->pipe_ends[0], STDIN_FILENO);
	}
	if (ms->pipes_struct->fd_file[3] >= 0)
	{
		close(STDOUT_FILENO);
		dup2(ms->pipes_struct->fd_file[3], STDOUT_FILENO);
		// close(ms->pipes_struct->fd_file[3]);
		ms->pipes_struct->fd_file[3] = -1;
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

int	execution(t_ms	*ms)
{
	char	*cmd_path;
	char	**env_arr;
	pid_t	pid;
	
	if (!ms->tokenlist)
		return (0);
	redirecting(ms);
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
