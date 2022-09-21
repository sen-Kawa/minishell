/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/09/21 17:12:42 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	b_exit(char *command)
{
	int		i;
	char	*needle;

	i = 0;
	while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'))
		i++;
	needle = ft_strnstr(&command[i], "exit", 5);
	if (!needle)
		return ;
	else if (needle[4] == ' ' || needle[4] == '\0')
		exit(EXIT_SUCCESS);
}

int	b_env(char *token, char **envp)
{
	int i;
	int	result;

	result = ft_strncmp(token, "env\0", 4);
	if (result == 0)
	{
		i = 0;
		while (envp[i])
		{
			ft_printf("%s\n", envp[i]);
			i++;
		}
		
	 return (1);
	}
	return (0);
}

t_env	*ft_envvnew(char *content)
{
	t_env	*new_list;

	new_list = malloc(sizeof (t_env));
	if (!new_list)
		return (NULL);
	new_list->content= content;
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

void print_env(t_ms	*ms)
{
	while(ms->env_list)
	{
		printf("%s\n", ms->env_list->content);
		ms->env_list = ms->env_list->next;
	}
}

int	b_export(t_ms	*ms, char **envp)
{
	int	i;
	t_env	*new;
	int	result;
	t_ms_list	*tmp;
	
	i = 0;
	while(envp[i])
	{
		new = ft_envvnew(envp[i]);
		ft_envvadd_back(&ms->env_list, new);
		i++;
	}
	tmp = ms->tokenlist;
	while(tmp)
	{
		result = ft_strncmp(tmp->token, "export\0", 7);
		if (result == 0 && tmp->next == NULL)
		{//print ordered list
			print_env(ms);
		}
		else if (result == 0 && tmp->next != NULL)
		{
			if (ft_strchr(tmp->next->token, '='))
			{
				new = ft_envvnew(tmp->next->token);
				ft_envvadd_back(&ms->env_list, new);
				i++;
				print_env(ms);
			}
			else
				return (i);
		}
		tmp = tmp->next;
	}
	
	// print_env(ms);
	return (i);
}

