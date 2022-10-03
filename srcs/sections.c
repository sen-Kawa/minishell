/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/03 13:47:12 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static t_ms_list	*sections_core(t_ms_list *tmp, int section)
{
	t_ms_list	*del;

	while (tmp && tmp->next)
	{
		if (!ft_strncmp(tmp->next->token, "|\0", 2))
		{
			if (tmp->next->next != NULL)
			{
				del = tmp->next;
				tmp->next = tmp->next->next;
				free (del);
				section++;
			}
		}
		tmp->next->section = section;
		tmp = tmp->next;
	}
	return (tmp);
}

void	sections(t_ms	*ms)
{
	t_ms_list	*tmp;
	int			section;

	tmp = ms->tokenlist;
	section = 0;
	if (!ft_strncmp(tmp->token, "|\0", 2))
	{
		ft_printf("cli: syntax error near unexpected token `|'\n");
		ms->lex->error = 3;
		return ;
	}
	tmp = sections_core(tmp, section);
	if (!ft_strncmp(tmp->token, "|\0", 2))
	{
		ft_printf("cli: syntax error near unexpected token `|'\n");
		ms->lex->error = 3;
		return ;
	}
}
