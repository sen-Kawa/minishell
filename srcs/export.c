/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/15 09:41:47 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	b_export(t_ms	*ms)
{
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (!tmp || (ft_strncmp(tmp->token, "export\0", 7) != 0))
		return (0);
	if (tmp->next == NULL
		|| (tmp->next && tmp->next->section > ms->current_section))
		make_array(ms, ms->env_lst_size);
	else if (tmp->next->section == ms->current_section
		&& (!ft_strchr(tmp->next->token, '=')
			|| ft_strlen(tmp->next->token) == 1 || tmp->next->token[0] == '='))
	{
		ft_printf("ksh: export: `%s': not a valid identifier\n",
			tmp->next->token);
		ms->exit_status = 1;
		return (1);
	}
	while (tmp)
	{
		b_export_var(tmp->token, ms);
		tmp = tmp->next;
	}
	ms->exit_status = 0;
	return (1);
}

void	b_export_var(char *token, t_ms *ms)
{
	char		**splitted;
	char		*copy;
	t_env		*new;
	t_env		*tmp_env;

	if (ft_strchr(token, '='))
	{
		copy = ft_strdup(token);
		splitted = ft_split(copy, '=');
		tmp_env = ms->env_list;
		while (tmp_env && tmp_env->next
			&& ft_strncmp(token, tmp_env->content, ft_strlen(splitted[0])))
			tmp_env = tmp_env->next;
		if (!ft_strncmp(token, tmp_env->content, ft_strlen(splitted[0])))
			tmp_env->content = token;
		else
		{
			new = ft_envvnew(token);
			ft_envvadd_back(&ms->env_list, new);
			ms->env_lst_size++;
		}
		free(splitted);
	}
}
