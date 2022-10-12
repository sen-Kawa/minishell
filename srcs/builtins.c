/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 17:24:50 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	b_exit(t_ms	*ms)
{
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (!tmp || ft_strncmp(tmp->token, "exit\0", 4) != 0)
		return (0);
	if (tmp->next == NULL)
		exit (0);
	else if (tmp->next != NULL)
	{
		b_exit_arg(tmp->next->token);
		if (tmp->next->next != NULL)
		{
			ft_printf("ksh: exit: too many arguments\n");
			ms->exit_status = 127;
		}
		else
			exit (ft_atoi(tmp->next->token));
	}
	return (1);
}

void	b_exit_arg(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_isdigit(token[i]))
			i++;
		else
		{
			ft_printf("ksh: exit: %s: numeric argument required\n", token);
			exit(2);
		}
	}
}

int	b_env(char *token, t_ms *ms)
{
	int		result;
	t_env	*tmp;

	tmp = ms->env_list;
	if (!token)
		return (0);
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

int	b_unset(t_ms	*ms)
{
	t_ms_list	*tmp;
	t_env		*envlst;
	t_env		*prev_envlst;

	tmp = ms->tokenlist;
	envlst = ms->env_list;
	if (!tmp || ft_strncmp(tmp->token, "unset", 5) != 0)
		return (0);
	if (tmp->next != NULL)
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
			modify_env_list(prev_envlst, envlst, ms);
	}
	ms->exit_status = 0;
	return (1);
}

void	modify_env_list(t_env *prev_envlst, t_env *envlst, t_ms *ms)
{
	prev_envlst->next = envlst->next;
	free (envlst);
	ms->env_lst_size--;
}
