/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:31:23 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 14:09:46 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	printing_tokens(t_ms_list *tokens)
{
	while (tokens)
	{
		ft_printf("Token: %s\tType: %s\tSect.: %i\tDollar: %i\n", tokens->token, tokens->type, tokens->section, tokens->dollar);
		tokens = tokens->next;
	}
	ft_printf("___\n");
	ft_printf(" Token \n");
}

void    print_to_out(t_ms *ms, char *to_print)
{
	int fd;

	if (ms->pipes_struct->fd_file[1] != -1)
		fd = ms->pipes_struct->fd_file[1];
	else
		fd = 1;
	ft_putstr_fd(to_print, fd);
}
