/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/11 19:34:56 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static t_ms_list	*sections_core(t_ms_list *tmp, t_ms *ms)
{
	t_ms_list	*del;
	// char	**splitted;
	// char	*copy;
	// t_ms_list	*newbe;
	// int	i;

	// i = 1;
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
		// else if (ft_strchr(tmp->token, '|'))
		// {
		// 	copy = ft_strdup(tmp->token);
		// 	splitted = ft_split(copy, '|');
		// 	tmp->token = splitted[0];
		// 	ms->sections++;
		// 	while (splitted[i])
		// 	{
		// 		newbe = ft_tokennew(splitted[i], "divided pipe");
		// 		ft_tokenadd_back(&tmp, newbe);
		// 		ms->sections++;
		// 	}
		// 	free(splitted);
		// }
		// 	ft_printf("token with pipe without space\n");
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
	if (!tmp)
		return ;
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
