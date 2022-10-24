/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/10/24 16:20:38 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	dollar_double(t_ms_list *tokens, t_ms	*ms)
{
	t_ms_list	*tmp;
	char		**space_split;
	char		*new_space;

	tmp = tokens;
	space_split = NULL;
	if (tmp)
	{
		while (tmp)
		{
			new_space = NULL;
			if (tmp->dollar == 1)
			{
				space_split = ft_split_ssp(tmp->token, ' ');
				new_space = dollar_core(space_split, 0, ms);
			}
			if (new_space != NULL)
				tmp->token = new_space;
			tmp = tmp->next;
		}
	}
	if (space_split)
		free (space_split);
}

char	*all_dollar_splitting(int a, char **envp, \
char **dollar_split, char *new_dollar)
{
	int	ds;

	new_dollar = "";
	if (a == 0)
	{
		ds = 0;
		while (dollar_split[ds])
		{
			new_dollar = replacing_vars(envp, ds, dollar_split, new_dollar);
			ds++;
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

	new_space = "";
	while (space_split[i])
	{
		a = 0;
		while (space_split[i][a])
		{
			if (space_split[i][a] == '$')
			{
				tmp = make_array_env(ms);
				dollar_split = ft_split(space_split[i], '$');
				new_dollar = all_dollar_splitting(a, tmp, \
				dollar_split, new_dollar);
				if (new_dollar)
					space_split[i] = new_dollar;
				free (dollar_split);
				freeing_paths(tmp);
				break ;
			}
			a++;
		}
		new_space = ft_strjoin(new_space, space_split[i]);
		i++;
	}
	return (new_space);
}
