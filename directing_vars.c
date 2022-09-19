/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directing_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/09/19 14:37:25 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_vars(char **envp, char *var)
{
	char	*envp_var;
	int		i;

	i = 0;
	while (envp[i])
	{
		envp_var = ft_strnstr(envp[i], ft_strjoin(var, "=") \
		, ft_strlen(var) + 1);
		if (envp_var)
		{
			envp_var = ft_substr(envp[i], ft_strlen(var) + 1, 100);
			if (!envp_var)
				return (0);
			break ;
		}
		i++;
	}
	return (envp_var);
}

char	*replacing_vars(char **envp, int ds, char **dollar_split, char *new_dollar)
{
	char	*var;

	//printf("Dollar split at ds %s\n", dollar_split[ds]);
	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
		var = "";
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
//	free (dollar_split[ds]);
	dollar_split[ds] = var;
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
	new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
	// free(dollar_split[ds]);
	return (new_dollar);
}

char	*replacing_vars_middle_dollar(char **envp, int ds, char **dollar_split, char *new_dollar)
{
	char	*var;
	
	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
		var = "";
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
//	free (dollar_split[ds]);
	dollar_split[ds] = var;
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
	if (ds == 1)
	{
		new_dollar = ft_strjoin(dollar_split[0], dollar_split[1]);
		free (dollar_split[0]);
		free (dollar_split[1]);
		write(1, "here", 1);
	}
	else
	{
		new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
		free (dollar_split[ds]);
		write(1, "here", 1);
	}
	return (new_dollar);
}
/*
DESCRIPTION
PartII of redirecting().
Alters types of tokens for redirection purposes.
In case of << it gives types to the symbol and
the delimiter but doesn't split them if they are together

RETURN
-

PARAMETERS
tmp: linked list for tokens

EXTERNAL FUNCTIONS
-
*/
void	redir2(t_ms_list *tmp)
{
	if (tmp->token[0] == '<' && tmp->token[1] == '<')
	{
		if (tmp->token[2] != '\0')
			tmp->type = "sym+delim";
		else if (tmp->token[2] == '\0')
		{
			tmp->type = "heredoc_sym";
			if (tmp->next)
				tmp->next->type = "delim";
		}
	}
	if (tmp->token[0] && tmp->token[1] && !tmp->token[2])
	{
		if (tmp->token[0] == '>' && tmp->token[1] == '>')
		{
			tmp->type = "red_out_app";
			if (tmp->next)
				tmp->next->type = "app_outfile";
		}
	}
}

/*
DESCRIPTION
Alters types of tokens for redirection purposes.
- "<" chagens type of following node to "infile"
- ">" chagens type of following node to "outfile"
- "<<*" chagens type of node to "heredoc"
- ">>" chagens type of following node to "app_outfile"

RETURN
-

PARAMETERS
tokens: linked list for tokens

EXTERNAL FUNCTIONS
-
*/
void	redirecting(t_ms_list *tokens)
{
	t_ms_list	*tmp;

	tmp = tokens;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->token[0] == '<' && !tmp->token[1])
			{
				tmp->type = "red_in";
				if (tmp->next)
					tmp->next->type = "infile";
			}
			else if (tmp->token[0] == '>' && !tmp->token[1])
			{
				tmp->type = "red_out";
				if (tmp->next)
					tmp->next->type = "outfile";
			}
			redir2(tmp);
			tmp = tmp->next;
		}
	}
}
