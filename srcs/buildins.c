/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/06 11:47:11 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
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

int	b_env(char *token, t_ms *ms)
{
	int		result;
	t_env	*tmp;

	tmp = ms->env_list;
	result = ft_strncmp(token, "env\0", 4);
	if (result == 0)
	{
		while (tmp)
		{
			ft_printf("%s\n", tmp->content);
			tmp = tmp->next;
		}
		ms->exit_status = 0;
		return (1);
	}
	return (0);
}

int	b_export(t_ms	*ms)
{
	int			result;
	int			flag;
	t_ms_list	*tmp;
	t_env		*new;
	char *copy;
	t_env		*tmp_env;
	char 		**splitted;
	// t_env		*tmp_env_pre;
	
	flag = 0;
	tmp = ms->tokenlist;
	result = ft_strncmp(tmp->token, "export\0", 7);
	if (result == 0 && tmp->next == NULL)
	{
		make_array(ms, ms->env_lst_size);
		ms->exit_status = 0;
		return (1);
	}
	while (tmp)
	{
		if (result == 0 && ft_strchr(tmp->token, '='))
		{
			copy = ft_strdup(tmp->token);
			splitted = ft_split(copy, '=');
			tmp_env = ms->env_list;
			while (tmp_env && tmp_env->next && ft_strncmp(tmp->token, tmp_env->content, ft_strlen(splitted[0])))
				tmp_env = tmp_env->next;
			if (!ft_strncmp(tmp->token, tmp_env->content, ft_strlen(splitted[0])))
			{
				tmp_env->content = tmp->token;
				flag++;
			}
			else
			{
				new = ft_envvnew(tmp->token);
				ft_envvadd_back(&ms->env_list, new);
				ms->env_lst_size++;
				flag++;
			}
//			free(copy);
			free(splitted);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (flag > 0)
	{
		ms->exit_status = 0;
		return (1);
	}
	else
		return (0);
}

int	b_unset(t_ms	*ms)
{
	t_ms_list	*tmp;
	t_env		*envlst;
	t_env		*prev_envlst;

	tmp = ms->tokenlist;
	envlst = ms->env_list;
	if (ft_strncmp(tmp->token, "unset", 5) == 0 && tmp->next != NULL)
	{
		tmp = tmp->next;
		while (envlst && envlst->next && ft_strncmp(tmp->token,
				envlst->content, ft_strlen(tmp->token)) != 0)
		{
			prev_envlst = envlst;
			envlst = envlst->next;
		}
		if (ft_strncmp(tmp->token, envlst->content,
				ft_strlen(tmp->token)) == 0 && !ft_strchr(tmp->token, '='))
		{
			prev_envlst->next = envlst->next;
			free (envlst);
			ms->env_lst_size--;
			ms->exit_status = 0;
			return (1);
		}
	}
	return (0);
}

int	b_echo(t_ms	*ms)
{
	int			result;
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (tmp)
		result = ft_strncmp(tmp->token, "echo\0", 5);
	if (tmp->next)
	{
		if (result == 0 && tmp->next != NULL)
		{
			if (!ft_strncmp(tmp->next->token, "-n\0", 3))
			{
				if (tmp->next->next)
					ft_printf("%s", tmp->next->next->token);
			}
			else
				ft_printf("%s\n", tmp->next->token);
		ms->exit_status = 0;
		return (1);
		}
	}
	else if (result == 0 && tmp->next == NULL)
	{
		ft_printf("\n");
		ms->exit_status = 0;
		return (1);
	}
	return (0);
}
