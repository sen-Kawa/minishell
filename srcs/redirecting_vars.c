/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/27 09:26:15 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	delete_token(t_ms *ms);
void	freeing_prev(t_ms *ms, t_ms_list	*tmp_prev, t_ms_list	*tmp);

char	*get_vars(char **envp, char *var)
{
	char	*envp_var;
	char	*tmp;
	int		i;
	int		len_var;
	int		len_sub;

	tmp = ft_strjoin(var, "=");
	len_var = ft_strlen(tmp);
	i = 0;
	while (envp[i])
	{
		envp_var = ft_strnstr(envp[i], tmp, len_var);
		if (envp_var)
		{
			len_sub = ft_strlen(envp_var) - len_var;
			envp_var = ft_substr(envp[i], len_var, len_sub);
			if (!envp_var)
				return (0);
			break ;
		}
		i++;
	}
	free (tmp);
	return (envp_var);
}

char	*replacing_vars(char **envp, int ds, \
char **dollar_split, char *new_dollar)
{
	char	*var;

	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
	{
		var = "";
		dollar_split[ds] = var;
		return (new_dollar);
	}
	dollar_split[ds] = var;
	new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
	return (new_dollar);
}

char	*replacing_vars_middle_dollar(char **envp, int ds, \
char **dollar_split, char *new_dollar)
{
	char	*var;
	char	*tmp;

	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
		var = "";
	dollar_split[ds] = var;
	if (ds == 1)
	{
		new_dollar = ft_strjoin(dollar_split[0], dollar_split[1]);
		if (dollar_split[1])
		{
			dollar_split[1] = NULL;
			free (dollar_split[1]);
		}
		if (dollar_split[0])
		{
			dollar_split[0] = NULL;
			free (dollar_split[0]);
		}
	}
	else
	{
		tmp = new_dollar;
		new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
		if (dollar_split[ds][0] != 0)
		{
			dollar_split[ds] = NULL;
			free (dollar_split[ds]);
		}
		free (tmp);
	}
	return (new_dollar);
}

void	delete_token(t_ms *ms)
{
	t_ms_list	*tmp;
	t_ms_list	*tmp_prev;

	tmp = ms->tokenlist;
	tmp_prev = ms->tokenlist;
	freeing_prev(ms, tmp_prev, tmp);
}

void	freeing_node(t_ms_list *tmp)
{
	free(tmp->token);
	free(tmp);
}

void	freeing_prev(t_ms *ms, t_ms_list *tmp_prev, t_ms_list *tmp)
{
	if (!tmp)
		return ;
	if (!ft_strncmp(tmp->type, "delete", 6))
	{
		if (tmp_prev == tmp)
		{
			ms->tokenlist = ms->tokenlist->next;
			tmp = tmp->next;
			freeing_node(tmp_prev);
			tmp_prev = tmp;
		}
		else
		{
			tmp_prev->next = tmp_prev->next->next;
			freeing_node(tmp);
			tmp = tmp_prev->next;
		}
	}
	else
	{
		tmp_prev = tmp;
		tmp = tmp->next;
	}
	freeing_prev(ms, tmp_prev, tmp);
}
