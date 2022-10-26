/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/26 20:27:24 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	lex_continue(t_ms *ms);
void	add_token(char *command, t_ms *ms);
void	pipe_token(char *command, t_ms *ms);
void	quote_call(char *command, t_ms *ms);

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
	while (command[ms->lex->start] == ' ')
		ms->lex->start++;
	while (command[ms->lex->start + ms->lex->i] && *command
		&& ms->lex->error == 0)
	{
		if (ms->lex->start + ms->lex->i <= ms->lex->length)
		{
			if (command[ms->lex->start + ms->lex->i] == ' '
				|| command[ms->lex->start + ms->lex->i] == 124)
			{
				if (ms->lex->i > 0)
					add_token(command, ms);
				pipe_token(command, ms);
				while (command[ms->lex->start + ms->lex->i] == ' ')
					ms->lex->i++;
				ms->lex->start = ms->lex->start + ms->lex->i;
				ms->lex->i = -1;
			}
		}
		quote_call(command, ms);
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
	dollar_check(ms);
}

void	pipe_token(char *command, t_ms *ms)
{
	t_ms_list	*newbe;

	if (command[ms->lex->start + ms->lex->i] == 124)
	{
		newbe = ft_tokennew(ft_strdup("|"), "space");
		ft_tokenadd_back(&ms->tokenlist, newbe);
		ms->lex->i++;
	}
}

void	quote_call(char *command, t_ms *ms)
{
	ms->lex = double_quotes(command, ms);
	ms->lex = single_quotes(command, ms);
}
