/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/09/14 13:30:13 by ksura            ###   ########.fr       */
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
			if (tmp->token[0] && !tmp->token[1])
			{
				if (tmp->token[0] == '<')
				{
					tmp->type = "red_in";
					if (tmp->next)
						tmp->next->type = "infile";
				}
				else if (tmp->token[0] == '>')
				{
					tmp->type = "red_out";
					if (tmp->next)
						tmp->next->type = "outfile";
				}
			}
			else if (tmp->token[0] == '<' && tmp->token[1] == '<')
			{
				tmp->type = "heredoc";
			}
			else if (tmp->token[0] && tmp->token[1] && !tmp->token[2])
			{
				if (tmp->token[0] == '>' && tmp->token[1] == '>')
				{
					tmp->type = "red_out_app";
					if (tmp->next)
						tmp->next->type = "app_outfile";
				}
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
