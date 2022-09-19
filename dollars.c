/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/09/19 14:23:35 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	dollarizing(t_ms_list *tokens);

char	*replacing_vars(char **envp, int ds \
, char **dollar_split, char *new_dollar);
char	*replacing_vars_middle_dollar(char **envp, int ds \
, char **dollar_split, char *new_dollar);
char	*all_dollar_splitting(int a, char **envp \
, char **dollar_split, char *new_dollar);
char	*dollar_core(char **envp, char **space_split, int i);

void	dollarizing(t_ms_list *tokens)
{
	t_ms_list	*tmp;
	int			i;

	tmp = tokens;
	if (tmp)
	{
		while (tmp)
		{
			i = 0;
			while (tmp->token[i])
			{
				if (tmp->token[i] == '$')
				{
					if (ft_strncmp(tmp->type, "single quotes", 2) != 0)
						tmp->dollar = 1;
				}
				i++;
			}
			tmp = tmp->next;
		}
	}
}

// void	dollar_outside(t_ms_list *tokens, char **envp)
// {
// 	t_ms_list	*tmp;
// 	char		**space_split;
// 	char		*new_space;

// 	tmp = tokens;
// 	new_space = NULL;
// 	if (tmp)
// 	{
// 		while (tmp)
// 		{
// 			if (ft_strncmp(tmp->type, "double quotes", 15)
// 				!= 0 && tmp->dollar == 1)
// 			{
// 				space_split = ft_split_ssp(tmp->token, ' ');
// 				new_space = dollar_core(envp, space_split, 0);
// 			}
// 			if(new_space != NULL)
// 				tmp->token = new_space;
// 			tmp = tmp->next;
// 		}
// 	}
// 	free (tmp);
// }

void	dollar_double(t_ms_list *tokens, char **envp)
{
	t_ms_list	*tmp;
	char		**space_split;
	char		*new_space;

	tmp = tokens;
	new_space = NULL;
	if (tmp)
	{
		while (tmp)
		{
			// if (ft_strncmp(tmp->type, "double quotes", 15)
			// 	== 0 && tmp->dollar == 1)
			if (tmp->dollar == 1)
			{
				space_split = ft_split_ssp(tmp->token, ' ');
				new_space = dollar_core(envp, space_split, 0);
			}
			if(new_space != NULL)
				tmp->token = new_space;
			tmp = tmp->next;
		}
	}
	free (space_split);
}

char	*all_dollar_splitting(int a, char **envp, char **dollar_split, char *new_dollar)
{
	int ds;
	
	new_dollar = "";
	if (a == 0)
	{
		ds = 0;
		while(dollar_split[ds])
		{
			new_dollar = replacing_vars(envp, ds, dollar_split, new_dollar);
			ds++;
		}
	}
	else if (a != 0)
	{
		ds = 1;
		while(dollar_split[ds])
		{
			new_dollar = replacing_vars_middle_dollar(envp, ds, dollar_split, new_dollar);
			ds++;
		}
	}
	return (new_dollar);
}

char	*dollar_core(char **envp, char **space_split, int i)
{
	char		*new_dollar;
	char		**dollar_split;
	char		*new_space;
	int			a;

	new_space = "";
	while (space_split[i])
	{
		a = 0;
		while (space_split[i][a])
		{
			if (space_split[i][a] == '$')
			{
				// printf("dollar found in string %i in character %i\n", i, a);
				dollar_split = ft_split(space_split[i], '$');
			//	free (space_split[i]);
				new_dollar = all_dollar_splitting(a, envp, dollar_split, new_dollar);
				if (new_dollar)
					space_split[i] = new_dollar;
				free (dollar_split);
			}
			a++;
		}
		// printf("string %i: %s\n", i, space_split[i]);
		new_space = ft_strjoin(new_space, space_split[i]);
		i++;
	}
	return (new_space);
}
