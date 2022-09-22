/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/09/22 16:15:32 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	execute(t_ms_list *tokens, char **envp)
{
	t_ms_list	*tmp;
	size_t	len;
	
	len = 0;
	tmp = tokens;
	(b_pwd(tokens->next->token, envp));
}
