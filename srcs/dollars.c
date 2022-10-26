/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/10/26 18:43:04 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	dollar_check(t_ms *ms);
t_ms_list	*old_token(char **new_space, t_ms_list *tmp);

/*
DESCRIPTION
Alters dollar variable (from default (0) to 1) of tokens
for replacing variables if it finds "$" in the token.
Doesn't change it for type "single quotes".

RETURN
-

PARAMETERS
tokens: linked list for tokens

EXTERNAL FUNCTIONS
-
*/

void	dollarizing(t_ms *ms)
{
	int			i;
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (tmp)
	{
		while (tmp)
		{
			i = 0;
			while (tmp->token[i])
			{
				replacing_exit(ms, i, tmp);
				i++;
			}
			tmp = tmp->next;
		}
	}
}

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
				printf("call double quote function\n");
			else
			{
				printf("split at dollar called\n");
				split_at_dollar(ms, tmp);
			}
		}
		tmp = tmp->next;
	}
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
	merged = merge_splits(splitted, i, 0);
	printf("merged: %s\n", merged);
	free(merged);
	freeing_paths(splitted);
}

char	*merge_splits(char **splitted, int total, int i)
{
	char	*merged;
	char	*prev_merge;
	
/*	int	len;

	len = 0;
	while (i >= 0)
	{
		len += ft_strlen(splitted[i]);
		i--;
	}
	merged = malloc(sizeof(char) * (len + 1));
*/
	if (total == 0)
		return (merged);
//	merged = NULL;
	prev_merge = merged;
	merged = ft_strjoin(merged, splitted[i]);
	if (i != 0)
		free(prev_merge);
	merge_splits(splitted, total - 1, i + 1);
}

void	dollar_double(t_ms_list *tokens, t_ms	*ms)
{
	t_ms_list	*tmp;
	char		**space_split;
	char		*new_space;
	char		**tmp_space_split;

	tmp = tokens;
	space_split = NULL;
	if (tmp)
	{
		while (tmp)
		{
			new_space = NULL;
			if (tmp->dollar == 1)
			{
				tmp_space_split = space_split;
				space_split = ft_split_ssp(tmp->token, ' ');
				if (tmp_space_split != NULL)
				{
					tmp_space_split = NULL;
					free(tmp_space_split);
				}
				new_space = dollar_core(space_split, 0, ms);
			}
			tmp = old_token(&new_space, tmp);
		}
	}
	if (space_split)
	{
		freeing_paths(space_split);
		free(tmp_space_split);
	}
}

t_ms_list	*old_token(char **new_space, t_ms_list *tmp)
{
	char	*old_token;

	if (*new_space != NULL)
	{
		old_token = tmp->token;
		tmp->token = *new_space;
		free (old_token);
	}
	tmp = tmp->next;
	return (tmp);
}

char	*all_dollar_splitting(int a, char **envp, \
char **dollar_split, char *new_dollar)
{
	int		ds;
	char	*tmp_new_d;

	new_dollar = NULL;
	if (a == 0)
	{
		ds = 0;
		while (dollar_split[ds])
		{
			tmp_new_d = new_dollar;
			new_dollar = replacing_vars(envp, ds, dollar_split, new_dollar);
			ds++;
			if (new_dollar != NULL)
				free (tmp_new_d);
			// printf("ds:%i\n", ds);
		}
	}
	else if (a != 0)
	{
		ds = 1;
		while (dollar_split[ds])
		{
			new_dollar = replacing_vars_middle_dollar(envp, ds, \
			dollar_split, new_dollar);
			ds++;
		}
	}
	return (new_dollar);
}

char	*dollar_core(char **space_split, int i, t_ms *ms)
{
	char		*new_dollar;
	char		**dollar_split;
	char		*new_space;
	int			a;
	char		**tmp;
	char		*tmp_new_space;

	new_space = NULL;
	new_dollar = NULL;
	while (space_split[i])
	{
		a = 0;
		while (space_split[i][a])
		{
			if (space_split[i][a] == '$')
			{
				tmp = make_array_env(ms);
				dollar_split = ft_split(space_split[i], '$');
				if (*dollar_split == NULL)
				{
					free(dollar_split);
					freeing_paths(tmp);
					//space_split[i] = NULL;
				}
				else
				{
					new_dollar = all_dollar_splitting(a, tmp, \
					dollar_split, new_dollar);
					if (new_dollar)
					{
						free (space_split[i]);
						space_split[i] = new_dollar;
					}
					freeing_paths(tmp);
					if (i >= 0)
						freeing_paths (dollar_split);
					else
						free (dollar_split);
					break ;
				}
			}
			a++;
		}
		tmp_new_space = new_space;
		// if (space_split[i] != NULL)
			new_space = ft_strjoin(new_space, space_split[i]);
		// if (tmp_new_space != NULL)
		{
			// tmp_new_space = NULL;
			free (tmp_new_space);
		}
		// if (new_dollar != NULL)
		// 	free (space_split[i]);
		i++;
		// printf("%i", i);
	}
	return (new_space);
}
