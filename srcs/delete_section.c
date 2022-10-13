/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/13 18:00:23 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	delete_section(t_ms *ms)
{
	t_ms_list	*tmp;

	while (ms->tokenlist && ms->tokenlist->section < ms->current_section)
	{
			tmp = ms->tokenlist;
			ms->tokenlist = ms->tokenlist->next;
			free(tmp);
	}
}
