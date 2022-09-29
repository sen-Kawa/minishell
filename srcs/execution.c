/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/09/29 13:30:40 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute(t_ms *ms)
{
	t_ms_list	*tmp;
	size_t	len;
	
	len = 0;
	tmp = ms->tokenlist;
	b_pwd(ms);
	b_export(ms);
	b_unset(ms);
	b_echo(ms);
	b_cd(ms);
	while(tmp)
	{
		len = ft_strlen(tmp->token);
		if (b_env(tmp->token, ms) && len < 3)
		{
			tmp = tmp->next;
			break;
		}
		tmp = tmp->next;
	}
	return ;
}
