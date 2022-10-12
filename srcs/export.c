/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 14:42:58 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	b_export(t_ms	*ms)
{
	char		*copy;
	char		**splitted;
	t_env		*new;
	t_env		*tmp_env;
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (!tmp || (ft_strncmp(tmp->token, "export\0", 7) != 0))
		return (0);
	if (tmp->next == NULL)
		make_array(ms, ms->env_lst_size);
	else if ((!ft_strchr(tmp->next->token, '=') || ft_strlen(tmp->next->token) == 1 || tmp->next->token[0] == '='))
	{
		ft_printf("ksh: export: `%s': not a valid identifier\n", tmp->next->token);
		ms->exit_status = 1;
		return (1);
	}
	while (tmp)
	{
		if (ft_strchr(tmp->token, '='))
		{
			copy = ft_strdup(tmp->token);
			splitted = ft_split(copy, '=');
			tmp_env = ms->env_list;
			while (tmp_env && tmp_env->next && ft_strncmp(tmp->token, tmp_env->content, ft_strlen(splitted[0])))
				tmp_env = tmp_env->next;
			if (!ft_strncmp(tmp->token, tmp_env->content, ft_strlen(splitted[0])))
				tmp_env->content = tmp->token;
			else
			{
				new = ft_envvnew(tmp->token);
				ft_envvadd_back(&ms->env_list, new);
				ms->env_lst_size++;
			}
			free(splitted);
		}
		tmp = tmp->next;
	}
	ms->exit_status = 0;
	return (1);
}
