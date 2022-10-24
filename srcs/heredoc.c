/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/24 15:14:43 by kaheinz          ###   ########.fr       */
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
	while (1)
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
		if (hereline)
			free (hereline);
	}
	tmp_heredoc(ms, herecom);
	free(herecom);
}

void	here_command(char *hereline, char **herecom)
{
	char *tmp;

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
