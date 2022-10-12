/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 16:18:17 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
t_lex	*double_quotes(char *command, t_ms *ms)
{
	t_ms_list	*newbe;
	char		*part;

	if (command[ms->lex->start + ms->lex->i] == '"')
	{
		ms->lex->i++;
		while (command[ms->lex->start + ms->lex->i]
			&& command[ms->lex->start + ms->lex->i] != '"')
			ms->lex->i++;
		if (command[ms->lex->start + ms->lex->i] != '"')
		{
			ms->lex->error = 1;
			return (ms->lex);
		}
		part = ft_substr(command, ms->lex->start + 1, ms->lex->i - 1);
		newbe = ft_tokennew(part, "double quotes");
		ft_tokenadd_back(&ms->tokenlist, newbe);
		ms->lex->i++;
		ms->lex = afterquotes(command, ms->lex, ms->tokenlist);
		ms->lex->start = ms->lex->start + ms->lex->i;
		ms->lex->i = -1;
	}
	return (ms->lex);
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
t_lex	*single_quotes(char *command, t_ms *ms)
{
	t_ms_list	*newbe;
	char		*part;

	if (command[ms->lex->start + ms->lex->i] == 39)
	{
		ms->lex->i++;
		while (command[ms->lex->start + ms->lex->i]
			&& command[ms->lex->start + ms->lex->i] != 39)
			ms->lex->i++;
		if (command[ms->lex->start + ms->lex->i] != 39)
		{
			ms->lex->error = 1;
			return (ms->lex);
		}
		part = ft_substr(command, ms->lex->start + 1, ms->lex->i - 1);
		newbe = ft_tokennew(part, "single quotes");
		ft_tokenadd_back(&ms->tokenlist, newbe);
		ms->lex->i++;
		ms->lex = afterquotes(command, ms->lex, ms->tokenlist);
		ms->lex->start = ms->lex->start + ms->lex->i;
		ms->lex->i = -1;
	}
	return (ms->lex);
}

t_lex	*beforequotes(char *command, t_lex *lex, t_ms_list *tokens)
{
	char		*part;
	t_ms_list	*newbe;

	if (command[lex->start + lex->i] == '"'
		|| command[lex->start + lex->i] == 39)
	{
		if (lex->i > 0)
		{
			if (!pipe_check(command, lex, tokens))
			{
				part = ft_substr(command, lex->start, lex->i);
				newbe = ft_tokennew(part, "beforequotes");
				ft_tokenadd_back(&tokens, newbe);
			}
		}
		lex->start = lex->start + lex->i;
		lex->i = 0;
	}
	return (lex);
}

t_lex	*afterquotes(char *command, t_lex *lex, t_ms_list *tokens)
{
	char		*part;
	t_ms_list	*newbe;

	if (command[lex->start + lex->i] != ' ' && command[lex->start + lex->i])
	{
		lex->start = lex->start + lex->i;
		lex->i = 0;
		while (command[lex->start + lex->i]
			&& *command && command[lex->i + lex->start] != ' ')
			lex->i++;
		part = ft_substr(command, lex->start, lex->i);
		newbe = ft_tokennew(part, "afterquotes_nospace");
		ft_tokenadd_back(&tokens, newbe);
	}
	return (lex);
}
