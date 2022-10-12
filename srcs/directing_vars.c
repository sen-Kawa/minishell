/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directing_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 16:55:16 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	delete_token(t_ms *ms);

static char	*get_vars(char **envp, char *var)
{
	char	*envp_var;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(var, "=");
	i = 0;
	while (envp[i])
	{
		envp_var = ft_strnstr(envp[i], tmp, ft_strlen(var) + 1);
		if (envp_var)
		{
			envp_var = ft_substr(envp[i], ft_strlen(var) + 1, 100);
			if (!envp_var)
				return (0);
			break ;
		}
		i++;
	}
	free (var);
	free (tmp);
	return (envp_var);
}

char	*replacing_vars(char **envp, int ds, \
char **dollar_split, char *new_dollar)
{
	char	*var;

	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
		var = "";
	dollar_split[ds] = var;
	new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
	return (new_dollar);
}

char	*replacing_vars_middle_dollar(char **envp, int ds, \
char **dollar_split, char *new_dollar)
{
	char	*var;

	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
		var = "";
	dollar_split[ds] = var;
	if (ds == 1)
	{
		new_dollar = ft_strjoin(dollar_split[0], dollar_split[1]);
		if (dollar_split[0])
			free (dollar_split[0]);
		if (dollar_split[1][0])
			free (dollar_split[1]);
	}
	else
	{
		new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
		if (dollar_split[ds])
			free (dollar_split[ds]);
	}
	return (new_dollar);
}

void	delete_token(t_ms *ms)
{
	t_ms_list	*tmp;
	t_ms_list	*tmp_prev;

	tmp = ms->tokenlist;
	tmp_prev = ms->tokenlist;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "delete", 6))
		{
			if (tmp_prev == tmp)
			{
				ms->tokenlist = ms->tokenlist->next;
				tmp = tmp->next;
				free(tmp_prev);
				tmp_prev = tmp;
			}
			else
			{
				tmp_prev->next = tmp_prev->next->next;
				free (tmp);
				tmp = tmp_prev->next;
			}
		}
		else
		{
			tmp_prev = tmp;
			tmp = tmp->next;
		}
	}
}
