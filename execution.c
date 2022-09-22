/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/09/22 16:25:03 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_ms_list *tokens, t_ms *ms, char **envp)
{
	t_ms_list	*tmp;
	size_t	len;
	
	len = 0;
	tmp = tokens;
	if (b_pwd(tokens->next->token, envp))
		return ;
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
