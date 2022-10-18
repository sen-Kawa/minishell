/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/18 17:02:01 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	lex_continue(t_ms *ms);
void	add_token(char *command, t_ms *ms);

/*
DESCRIPTION
Makes Nodes out of Commandline returned by readline

RETURN
void

PARAMETERS

EXTERNAL FUNCTIONS
ft_substr(), ft_tokennew(), ft_tokenaddback(), ft_strlen()
*/

void	tokenice(char *command, t_ms *ms)
{
	t_ms_list	*newbe;

	while (command[ms->lex->start] == ' ')
		ms->lex->start++;
	while (command[ms->lex->start + ms->lex->i] && *command)
	{
		if (ms->lex->start + ms->lex->i <= ms->lex->length)
		{
			if (command[ms->lex->start + ms->lex->i] == ' '
				|| command[ms->lex->start + ms->lex->i] == 124)
			{
				if (ms->lex->i > 0)
					add_token(command, ms);
				if (command[ms->lex->start + ms->lex->i] == 124)
				{
					newbe = ft_tokennew("|", "space");
					ft_tokenadd_back(&ms->tokenlist, newbe);
					ms->lex->i++;
				}
				while (command[ms->lex->start + ms->lex->i] == ' ')
					ms->lex->i++;
				ms->lex->start = ms->lex->start + ms->lex->i;
				ms->lex->i = -1;
			}
			ms->lex = beforequotes(command, ms->lex, ms->tokenlist);
		}
		ms->lex = double_quotes(command, ms);
		ms->lex = single_quotes(command, ms);
		if (ms->lex->error == 1)
			return ;
		ms->lex->i++;
	}
	if (ms->lex->i > 0)
		add_token(command, ms);
	lex_continue(ms);
}

void	add_token(char *command, t_ms *ms)
{
	char		*part;
	t_ms_list	*newbe;

	part = ft_substr(command, ms->lex->start, ms->lex->i);
	newbe = ft_tokennew(part, "space");
	ft_tokenadd_back(&ms->tokenlist, newbe);
}

void	lex_continue(t_ms *ms)
{
	sections(ms);
	dollarizing(ms);
	dollar_double(ms->tokenlist, ms);
}
