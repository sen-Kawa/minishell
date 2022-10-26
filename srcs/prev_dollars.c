/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prev_dollars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/10/26 20:27:53 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ms_list	*old_token(char **new_space, t_ms_list *tmp);

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
