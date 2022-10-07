/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/07 17:34:43 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static t_ms_list	*sections_core(t_ms_list *tmp, t_ms *ms)
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
				ms->sections++;
			}
		}
		tmp->next->section = ms->sections;
		tmp = tmp->next;
	}
	return (tmp);
}

void	sections(t_ms	*ms)
{
	t_ms_list	*tmp;
	tmp = ms->tokenlist;
	ms->sections = 0;
	ms->current_section = 0;
	if (!ft_strncmp(tmp->token, "|\0", 2))
	{
		ft_printf("cli: syntax error near unexpected token `|'\n");
		ms->lex->error = 3;
		return ;
	}
	tmp = sections_core(tmp, ms);
	if (!ft_strncmp(tmp->token, "|\0", 2))
	{
		ft_printf("cli: syntax error near unexpected token `|'\n");
		ms->lex->error = 3;
		return ;
	}
}
