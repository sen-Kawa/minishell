/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/10/20 19:00:46 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	checking_status(t_ms *ms, t_ms_list	*tmp, int i)
{
	char	*token_ex;
	char	*sub;
	char	*remain;
	char	*replaced;
	char	*status;

	token_ex = tmp->token;
	sub = ft_substr(token_ex, 0, i);
	remain = ft_substr(token_ex, i + 2, ft_strlen(token_ex));
	if (WIFEXITED(ms->exit_status))
		status = ft_itoa(WEXITSTATUS(ms->exit_status));
	else if (WIFSIGNALED(ms->exit_status)
		&& ms->pipes_struct->child_pid[0] != -1)
		status = ft_itoa(128 + WTERMSIG(ms->exit_status));
	else
		status = ft_itoa(ms->exit_status);
	replaced = ft_strjoin(sub, status);
	tmp->token = ft_strjoin(replaced, remain);
	free_status(status, replaced, remain, sub);
	free(token_ex);
}

void	replacing_exit(t_ms *ms, int i, t_ms_list	*tmp)
{
	if (tmp->token[i] == '$'
		&& (ft_strncmp(tmp->type, "single quotes", 2) != 0))
	{
		tmp->dollar = 1;
		if (tmp->token[i + 1] == '?')
		{
			checking_status(ms, tmp, i);
			tmp->type = "int";
			tmp->dollar = 0;
		}
	}
}
