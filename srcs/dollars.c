/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/10/26 20:32:17 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	dollar_check(t_ms *ms)
{
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->dollar == 1)
		{
			if (ft_strncmp(tmp->type, "double quotes", 14) == 0)
				split_in_quotes(ms, tmp);
			else
			{
				split_at_dollar(ms, tmp);
			}
		}
		tmp = tmp->next;
	}
}

void	split_in_quotes(t_ms *ms, t_ms_list *node)
{
	char	**splitted;
	char	*merged;
	int		i;

	i = 0;
	splitted = ft_split_ssp(node->token, ' ');
	while (splitted[i])
	{
		split_dollar_quotes(ms, &splitted[i]);
		i++;
	}
	merged = NULL;
	merge_splits(&merged, splitted, i, 0);
	free (node->token);
	node->token = merged;
	freeing_paths(splitted);
}

void	split_dollar_quotes(t_ms *ms, char **split)
{
	char	**split_dollar;
	char	**env_array;
	char	*merged;
	char	*var;
	int		i;

	i = 0;
	if (!ft_strchr(*split, '$'))
		return ;
	split_dollar = ft_split(*split, '$');
	while (split_dollar[i])
	{
		env_array = make_array_env(ms);
		var = get_vars(env_array, split_dollar[i]);
		free(split_dollar[i]);
		split_dollar[i] = var;
		i++;
		freeing_paths(env_array);
	}
	merged = NULL;
	merge_splits(&merged, split_dollar, i, 0);
	free (*split);
	*split = merged;
	freeing_paths(split_dollar);
}

void	split_at_dollar(t_ms *ms, t_ms_list *node)
{
	char	**splitted;
	char	**env_array;
	char	*var;
	int		i;
	char	*merged;

	i = 0;
	splitted = ft_split(node->token, '$');
	while (splitted[i])
	{
		env_array = make_array_env(ms);
		var = get_vars(env_array, splitted[i]);
		free(splitted[i]);
		splitted[i] = var;
		i++;
		freeing_paths(env_array);
	}
	merged = NULL;
	merge_splits(&merged, splitted, i, 0);
	free (node->token);
	node->token = merged;
	freeing_paths(splitted);
}

void	merge_splits(char	**merged, char **splitted, int total, int i)
{
	char	*prev_merge;

	if (total == 0)
		return ;
	prev_merge = *merged;
	*merged = ft_strjoin(*merged, splitted[i]);
	if (i != 0)
		free(prev_merge);
	merge_splits(merged, splitted, total - 1, i + 1);
}
