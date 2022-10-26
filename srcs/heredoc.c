/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/26 20:57:49 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	null_hereline(t_ms *ms, char *delim);
void	free_hereline(char *hereline);

void	heredoc(t_ms *ms, char	*delim)
{
	char		*hereline;
	char		*herecom;

	hereline = "";
	herecom = NULL;
	while (1)
	{
		hereline = readline("> ");
		if (hereline == NULL)
		{
			null_hereline(ms, delim);
			break ;
		}
		if (!ft_strncmp(hereline, delim, sizeof(delim)))
		{
			free_hereline(hereline);
			ms->pipes_struct->fd_file[0] = open(".tmp_heredoc",
					O_RDONLY | O_CREAT | O_TRUNC, 0777);
			break ;
		}
		here_command(hereline, &herecom);
		free_hereline(hereline);
	}
	tmp_heredoc(ms, herecom);
	free(herecom);
}

void	null_hereline(t_ms *ms, char *delim)
{
	ft_printf("ksh: warning: \
		here-document delimited by end-of-file(wanted `%s')\n", delim);
	ms->exit_status = 1;
}

void	free_hereline(char *hereline)
{
	if (hereline)
		free (hereline);
}

void	here_command(char *hereline, char **herecom)
{
	char	*tmp;

	if (herecom)
	{
		tmp = *herecom;
		*herecom = ft_strjoin(tmp, hereline);
		free (tmp);
		tmp = *herecom;
		*herecom = ft_strjoin(tmp, "\n");
		free (tmp);
	}
	else
	{
		tmp = *herecom;
		*herecom = ft_strjoin(hereline, "\n");
		free (tmp);
	}
}

void	tmp_heredoc(t_ms *ms, char *herecom)
{
	if (herecom)
	{
		ms->pipes_struct->fd_file[0] = open(".tmp_heredoc",
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (ms->pipes_struct->fd_file[0] != -1)
			ft_putstr_fd(herecom, ms->pipes_struct->fd_file[0]);
		close(ms->pipes_struct->fd_file[0]);
		ms->pipes_struct->fd_file[0] = open(".tmp_heredoc", O_RDONLY);
	}
}
