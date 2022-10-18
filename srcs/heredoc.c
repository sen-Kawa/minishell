/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/18 13:28:17 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

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
			ft_printf("ksh: warning: \
				here-document delimited by end-of-file(wanted `%s')\n", delim);
			ms->exit_status = 1;
			break ;
		}
		if (!ft_strncmp(hereline, delim, sizeof(delim)))
		{
			if (hereline)
				free (hereline);
			ms->pipes_struct->fd_file[0] = open(".tmp_heredoc",
					O_RDONLY | O_CREAT | O_TRUNC, 0777);
			break ;
		}
		here_command(hereline, &herecom);
	}
	tmp_heredoc(ms, herecom);
}

void	here_command(char *hereline, char **herecom)
{
	if (herecom)
	{
		*herecom = ft_strjoin(*herecom, hereline);
		*herecom = ft_strjoin(*herecom, "\n");
	}
	else
		*herecom = ft_strjoin(hereline, "\n");
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
