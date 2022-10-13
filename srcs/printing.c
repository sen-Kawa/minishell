/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:31:23 by ksura             #+#    #+#             */
/*   Updated: 2022/10/13 16:46:51 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	printing_tokens(t_ms_list *tokens)
{
	while (tokens)
	{
		ft_printf("Token: %s\tType: %s\tSect.: %i\tDollar: \
		%i\n", tokens->token, tokens->type, tokens->section, tokens->dollar);
		tokens = tokens->next;
	}
	ft_printf("___\n");
	ft_printf(" Token \n");
}

void	print_to_out(t_ms *ms, char *to_print)
{
	int	fd;

	if (ms->pipes_struct->fd_file[1] != -1)
		fd = ms->pipes_struct->fd_file[1];
	else if (ms->sections > 0 && (ms->current_section % 2) == 1)
		fd = ms->pipes_struct->pipe_ends[1];
	else if (ms->sections > 0 && (ms->current_section % 2) == 0)
		fd = ms->pipes_struct->pipe2_ends[1];
	else
		fd = 1;
	ft_putstr_fd(to_print, fd);
}
