/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/09/13 08:45:51 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
DESCRIPTION
Makes Node out of Command within Double Quotes

RETURN
Structure "lex" which contain, integers start, i & length

PARAMETERS
command.: returne of readline()
lex: structure for stuff
tokens: linked list for tokens

EXTERNAL FUNCTIONS
ft_substr(), ft_tokennew(), ft_tokenaddback()
*/
t_lex_struct	double_quotes(char *command, t_lex_struct lex, t_ms_list *tokens)
{
	t_ms_list	*newbe;
	char		*part;
	
	if (command[lex.start + lex.i] == '"')
		{
			lex.i++;
			while (command[lex.start + lex.i] && command[lex.start + lex.i] != '"')
				lex.i++;
			if(command[lex.start + lex.i] != '"')
			{
				lex.error = 1;
				return (lex);
			}
			part = ft_substr(command, lex.start + 1, lex.i - 1);
			newbe = ft_tokennew(part, "double quotes");
			ft_tokenadd_back(&tokens, newbe);
			lex.i++;
			lex.start = lex.start + lex.i;
			lex.i = 0;
		}
		return (lex);
}

/*
DESCRIPTION
Makes Node out of Command within Single Quotes

RETURN
Structure "lex" which contain, integers start, i & length

PARAMETERS
command.: returne of readline()
lex: structure for stuff
tokens: linked list for tokens

EXTERNAL FUNCTIONS
ft_substr(), ft_tokennew(), ft_tokenaddback()
*/
t_lex_struct	single_quotes(char *command, t_lex_struct lex, t_ms_list *tokens)
{
	t_ms_list	*newbe;
	char		*part;
	
	if (command[lex.start + lex.i] == 39)
		{
			lex.i++;
			while (command[lex.start + lex.i] && command[lex.start + lex.i] != 39)
				lex.i++;
			if(command[lex.start + lex.i] != 39)
			{
				lex.error = 1;
				return (lex);
			}
			part = ft_substr(command, lex.start + 1, lex.i - 1);
			newbe = ft_tokennew(part, "single quotes");
			ft_tokenadd_back(&tokens, newbe);
			lex.i++;
			lex.start = lex.start + lex.i;
			lex.i = 0;
		}
		return (lex);
}

void	freeing_tokens(t_ms_list	*tokens)
{
	t_ms_list	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
}
/*
DESCRIPTION
Makes Nodes out of Commandline returned by readline

RETURN
void

PARAMETERS

EXTERNAL FUNCTIONS
ft_substr(), ft_tokennew(), ft_tokenaddback(), ft_strlen()
*/
t_lex_struct	tokenice(char *command, t_ms_list *tokens)
{
	char *part;
	t_ms_list		*newbe;
	t_lex_struct	lex;
	
	lex.i = 0;
	lex.start = 0;
	lex.error = 0;
	lex.length = ft_strlen(command);
	printf("The Length is:%i\n", lex.length);
	while (command[lex.start] == ' ')
		lex.start++;
	while(command[lex.start + lex.i] && *command)
	{
	
		// space_lex(command, lex, tokens)
		if (lex.start + lex.i <= lex.length)
		{
			if (command[lex.start +lex.i] == ' ')
			{
				// write(1, "inside 1\n", 10);
				if (lex.i > 0)
				{
					part = ft_substr(command,lex. start, lex.i);
					newbe = ft_tokennew(part, "space");
					ft_tokenadd_back(&tokens, newbe);
					// free(part);
				}
				while (command[lex.start + lex.i] == ' ')
					lex.i++;
				lex.start = lex.start + lex.i;
				lex.i = -1;
			}
		}
		
		lex.i++;
		lex = double_quotes(command, lex, tokens);
		lex = single_quotes(command, lex, tokens);
		if (lex.error == 1)
		{
			write(1, "bash: syntax error, quotes missing\n", 36);
			return (lex);
		}
			
	}
	if (lex.i > 0)
	{
		// write(1, "inside 2\n", 10);
		part = ft_substr(command, lex.start, lex.i);
		newbe = ft_tokennew(part, "space_before");
		// free(part);
		ft_tokenadd_back(&tokens, newbe);
	}
	return (lex);
}
