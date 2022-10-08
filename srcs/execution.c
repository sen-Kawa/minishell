/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/08 17:32:55 by ksura            ###   ########.fr       */
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
	// if (ms->pipes_struct->fd_file[0])
	// {
	// 	ms->pipes_struct->fd_file[2] = dup(STDIN_FILENO);
	// 	dup2(ms->pipes_struct->fd_file[0], STDIN_FILENO);
	// 	close(ms->pipes_struct->fd_file[0]);
	// }
	// if (ms->pipes_struct->fd_file[1])
	// {
	// 	ms->pipes_struct->fd_file[3] = dup(STDOUT_FILENO);
	// 	dup2(ms->pipes_struct->fd_file[1], STDOUT_FILENO);
	// 	close(ms->pipes_struct->fd_file[1]);
	// }
	sum = (b_pwd(ms) + b_export(ms) + b_unset(ms) + b_echo(ms) + b_cd(ms));
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

void	heredoc(t_ms *ms, char	*delim)
{
	char		*hereline;
	char		*herecom;

	hereline = "";
	herecom = NULL;
	while (ft_strncmp(hereline, delim, sizeof(delim)))
	{
		hereline = readline("> ");
		if (hereline == NULL)
		{
			ft_printf("ksh: warning: here-document delimited by end-of-file (wanted `%s')\n", delim);
			break ;
		}
		if (!ft_strncmp(hereline, delim, sizeof(delim)))
		{
			free (hereline);
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
		ms->pipes_struct->fd_file[0] = open(".tmp_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (ms->pipes_struct->fd_file[0] != -1)
			ft_putstr_fd(herecom, ms->pipes_struct->fd_file[0]);
	}
}


int	execution(t_ms	*ms)
{
	char	*cmd_path;
	char	**env_arr;
	pid_t	pid;
	// t_ms_list	*tmp_token_lst;
	
	if (ms->sections == 0)
	{
		if (builtins(ms) > 0)
			return (0);
		env_arr = make_array_env(ms);
		cmd_path = get_cmd_path(ms->tokenlist->token, env_arr);
		pid = fork();
		perror("error fork");
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			ft_printf("fd 0 is: %i", ms->pipes_struct->fd_file[0]);
			if (ms->pipes_struct->fd_file[0] == 3)
			{
				dup2(ms->pipes_struct->fd_file[0], STDIN_FILENO);
				close(ms->pipes_struct->fd_file[0]);
				ms->pipes_struct->fd_file[0] = 0;
			}
			if (ms->pipes_struct->fd_file[1])
			{
				dup2(ms->pipes_struct->fd_file[1], STDOUT_FILENO);
				close(ms->pipes_struct->fd_file[1]);
				ms->pipes_struct->fd_file[1] = 0;
			}
			execve(cmd_path, make_array_token(ms), env_arr);
			exit (127);
		}
		waitpid(pid, &ms->exit_status, WUNTRACED);
		
	}
	
	// if (ms->sections == 1)
	// {
	// 	tmp_token_lst = ms->tokenlist;
	// 	env_arr = make_array_env(ms);
	// 	if (pipe(ms->pipes_struct->pipe_ends) == -1)
	// 		return (1);
	// 	cmd_path = get_cmd_path(ms->tokenlist->token, env_arr);
		
	// 	close(ms->pipes_struct->pipe_ens[0]);
	// 	close(ms->pipes_struct->pipe_ens[1]);
	// }
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
