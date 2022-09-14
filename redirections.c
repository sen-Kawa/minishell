/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/09/14 16:35:04 by ksura            ###   ########.fr       */
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

/*
DESCRIPTION
PartII of redirecting().
Alters types of tokens for redirection purposes.

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
