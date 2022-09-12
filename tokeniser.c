/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 19:04:32 by ksura            ###   ########.fr       */
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
			// write(1, "Quote\n", 7);
			lex.i++;
			while (command[lex.start + lex.i] != '"')
				lex.i++;
			
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
			// write(1, "Quote\n", 7);
			lex.i++;
			while (command[lex.start + lex.i] != 39)
				lex.i++;
			
			part = ft_substr(command, lex.start + 1, lex.i - 1);
			newbe = ft_tokennew(part, "single quotes");
			ft_tokenadd_back(&tokens, newbe);
			lex.i++;
			lex.start = lex.start + lex.i;
			lex.i = 0;
		}
		return (lex);
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
void	tokenice(char *command, t_ms_list *tokens)
{
	char *part;
	t_ms_list		*newbe;
	t_lex_struct	lex;
	
	lex.i = 0;
	lex.start = 0;
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
	}
	if (lex.i > 0)
	{
		// write(1, "inside 2\n", 10);
		part = ft_substr(command, lex.start, lex.i);
		newbe = ft_tokennew(part, "space_before");
		// free(part);
		ft_tokenadd_back(&tokens, newbe);
	}
	
}
