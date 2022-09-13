/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/09/13 19:30:19 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirecting(t_ms_list *tokens)
{
	t_ms_list	*tmp;
	
	tmp = tokens;
	if (tmp)
	{
		while(tmp)
		{
			if (*tmp->token == '<')
			{
				tmp->type = "red_in";
				tmp->next->type = "infile";
			}
			else if (*tmp->token == '>')
			{
				tmp->type = "red_out";
				tmp->next->type = "outfile";
			}
			tmp = tmp->next;
		}
	}
}