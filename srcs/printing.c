/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:31:23 by ksura             #+#    #+#             */
/*   Updated: 2022/10/03 13:50:26 by kaheinz          ###   ########.fr       */
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
