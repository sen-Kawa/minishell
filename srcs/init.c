/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:31:26 by kaheinz           #+#    #+#             */
/*   Updated: 2022/10/20 19:18:02 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init(t_ms	*ms, char *command)
{
	ms->pipes_struct->fd_file[0] = -1;
	ms->pipes_struct->fd_file[1] = -1;
	ms->pipes_struct->pipe_ends[0] = -1;
	ms->pipes_struct->pipe_ends[1] = -1;
	ms->pipes_struct->pipe2_ends[0] = -1;
	ms->pipes_struct->pipe2_ends[1] = -1;
	ms->lex->start = 0;
	ms->lex->i = 0;
	if (command)
		ms->lex->length = ft_strlen(command);
	ms->lex->error = 0;
}
