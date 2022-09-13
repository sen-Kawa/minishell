/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/09/13 19:59:33 by kaheinz          ###   ########.fr       */
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

void	dollarizing(t_ms_list *tokens)
{
	t_ms_list	*tmp;
	int	i;

	tmp = tokens;
	if (tmp)
	{
		while(tmp)
		{
			i = 0;
			while (tmp->token[i])
			{
				if (tmp->token[i] == '$')
				{
					if (ft_strncmp(tmp->type, "single quotes", 2) != 0)
						tmp->dollar = 1;
				}
				i++;
			}
			tmp = tmp->next;
		}
	}
}
