/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/09/13 17:59:43 by kaheinz          ###   ########.fr       */
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
	int			dlr;

	dlr = 0;
	if (command[lex.start + lex.i] == '"')
	{
		lex.i++;
		while (command[lex.start + lex.i] && command[lex.start + lex.i] != '"')
		{
			lex.i++;
			if (command[lex.start + lex.i] == '$')
				dlr = 1;
		}
			
		if(command[lex.start + lex.i] != '"')
		{
			lex.error = 1;
			return (lex);
		}
		part = ft_substr(command, lex.start + 1, lex.i - 1);
		if (dlr == 0)
			newbe = ft_tokennew(part, "double quotes", tokens->section);
		else
			newbe = ft_tokennew(part, "$double$quote$", tokens->section);
		ft_tokenadd_back(&tokens, newbe);
		lex.i++;
		lex = afterquotes(command, lex, tokens);
		lex.start = lex.start + lex.i;
		lex.i = -1;
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
		newbe = ft_tokennew(part, "single quotes", tokens->section);
		ft_tokenadd_back(&tokens, newbe);
		lex.i++;
		lex = afterquotes(command, lex, tokens);
		lex.start = lex.start + lex.i;
		lex.i = -1;
	}
	return (lex);
}


t_lex_struct	beforequotes(char *command, t_lex_struct lex, t_ms_list *tokens)
{
	char *part;
	t_ms_list		*newbe;

			if (command[lex.start +lex.i] == '"' || command[lex.start +lex.i] == 39)
			{
				if (lex.i > 0)
				{
					if (!pipe_check(command, lex, tokens))
					{
						part = ft_substr(command,lex. start, lex.i);
						newbe = ft_tokennew(part, "beforequotes", tokens->section);
						ft_tokenadd_back(&tokens, newbe);
					}
				}
				lex.start = lex.start + lex.i;
				lex.i = 0;
			}
	return (lex);
}

t_lex_struct	afterquotes(char *command, t_lex_struct lex, t_ms_list *tokens)
{
	char *part;
	t_ms_list		*newbe;

	if (command[lex.start + lex.i] != ' ' && command[lex.start + lex.i])
	{
		lex.start = lex.start + lex.i;
		lex.i = 0;
		while(command[lex.start + lex.i] && *command && command[lex.i + lex.start] != ' ')
			lex.i++;
		part = ft_substr(command, lex.start, lex.i);
		newbe = ft_tokennew(part, "afterquotes_nospace", tokens->section);
		ft_tokenadd_back(&tokens, newbe);
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

int	pipe_check(char *command, t_lex_struct lex, t_ms_list *tokens)
{
	if (command[lex.start + lex.i - 1] == '|' && command[lex.start + lex.i - 2] == ' ')
	{
		tokens->section++;
		return (1);
	}
	else if (command[lex.start + lex.i - 1] == '|' && command[lex.start + lex.i - 2] != ' ')
	{
		lex.error = 2;
		return (1);
	}
	return (0);
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
		if (lex.start + lex.i <= lex.length)
		{
			if (command[lex.start +lex.i] == ' ')
			{
				// write(1, "inside 1\n", 10);
				if (lex.i > 0)
				{
					if (!pipe_check(command, lex, tokens))
					{
						part = ft_substr(command,lex. start, lex.i);
						newbe = ft_tokennew(part, "space", tokens->section);
						ft_tokenadd_back(&tokens, newbe);
					}
				}
				while (command[lex.start + lex.i] == ' ')
					lex.i++;
				lex.start = lex.start + lex.i;
				lex.i = -1;
			}
			lex = beforequotes(command, lex, tokens);
		}
		lex = double_quotes(command, lex, tokens);
		lex = single_quotes(command, lex, tokens);
		if (lex.error == 1)
		{
			write(1, "bash: syntax error, quotes missing\n", 36);
			return (lex);
		}
		if (lex.error == 2)
			write(1, "bash: syntax error, space missing\n", 35);
		lex.i++;
	}
	if (lex.i > 0)
	{
		// write(1, "inside 2\n", 10);
		part = ft_substr(command, lex.start, lex.i);
		newbe = ft_tokennew(part, "space_before", tokens->section);
		// free(part);
		ft_tokenadd_back(&tokens, newbe);
	}
	return (lex);
}
