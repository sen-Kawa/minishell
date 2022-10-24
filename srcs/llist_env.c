/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/24 14:24:23 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_env	*ft_envvnew(char *content)
{
	t_env	*new_list;

	new_list = malloc(sizeof (t_env));
	if (!new_list)
		return (NULL);
	new_list->content = ft_strdup(content);
	new_list->next = NULL;
	return (new_list);
}

t_env	*ft_envvlast(t_env *envv)
{
	t_env	*last;

	if (!envv)
		return (NULL);
	last = envv;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_envvadd_back(t_env **env, t_env *new)
{
	if (!*env)
		*env = new;
	else
	{
		ft_envvlast(*env)->next = new;
	}
}

void	print_env(t_ms	*ms)
{
	while (ms->env_list)
	{
		printf("%s\n", ms->env_list->content);
		ms->env_list = ms->env_list->next;
	}
}

void	creating_env_list(char **envp, t_ms *ms)
{
	t_env	*new;

	ms->env_lst_size = 0;
	while (envp[ms->env_lst_size])
	{
		new = ft_envvnew(envp[ms->env_lst_size]);
		ft_envvadd_back(&ms->env_list, new);
		ms->env_lst_size++;
	}
}
