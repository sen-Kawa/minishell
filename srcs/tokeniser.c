/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/03 15:05:43 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	freeing_tokens(t_ms *ms)
{
	t_ms_list	*temp;

	while (ms->tokenlist != NULL)
	{
		temp = ms->tokenlist;
		ms->tokenlist = ms->tokenlist->next;
		free(temp);
	}
}

void	freeing_all(t_ms *ms)
{
	t_env	*tenv;

	freeing_tokens(ms);
	while (ms->env_list != NULL)
	{
		tenv = ms->env_list;
		ms->env_list = ms->env_list->next;
		free(tenv);
	}
}

int	pipe_check(char *command, t_lex *lex, t_ms_list *tokens)
{
	if (command[lex->start + lex->i - 1] == '|'
		&& command[lex->start + lex->i - 2] == ' ')
	{
		tokens->section++;
		return (1);
	}
	else if (command[lex->start + lex->i - 1]
		== '|' && command[lex->start + lex->i - 2] != ' ')
	{
		lex->error = 2;
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

t_lex	*tokenice(char *command, t_ms *ms, char **envp)
{
	char		*part;
	t_ms_list	*newbe;
	t_lex		*lex;

	(void) envp;
	lex = malloc(sizeof(t_lex));
	ms->lex = lex;
	ms->lex->i = 0;
	ms->lex->start = 0;
	ms->lex->error = 0;
	ms->lex->length = ft_strlen(command);
	// printf("The Length is:%i\n", lex.length);
	while (command[ms->lex->start] == ' ')
		ms->lex->start++;
	while (command[ms->lex->start + ms->lex->i] && *command)
	{
		if (ms->lex->start + ms->lex->i <= ms->lex->length)
		{
			if (command[ms->lex->start + ms->lex->i] == ' ')
			{
				if (ms->lex->i > 0)
				{
					part = ft_substr(command, ms->lex->start, ms->lex->i);
					newbe = ft_tokennew(part, "space");
					ft_tokenadd_back(&ms->tokenlist, newbe);
				}
				while (command[ms->lex->start + ms->lex->i] == ' ')
					ms->lex->i++;
				ms->lex->start = ms->lex->start + ms->lex->i;
				ms->lex->i = -1;
			}
			ms->lex = beforequotes(command, ms->lex, ms->tokenlist);
		}
		ms->lex = double_quotes(command, ms);
		ms->lex = single_quotes(command, ms->lex, ms->tokenlist);
		if (ms->lex->error == 1)
		{
			write(1, "bash: syntax error, quotes missing\n", 36);
			return (ms->lex);
		}
		if (ms->lex->error == 2)
			write(1, "bash: syntax error, space missing\n", 35);
		ms->lex->i++;
	}
	if (ms->lex->i > 0)
	{
		part = ft_substr(command, ms->lex->start, ms->lex->i);
		newbe = ft_tokennew(part, "space_before");
		ft_tokenadd_back(&ms->tokenlist, newbe);
	}
	redirecting(ms->tokenlist);
	sections(ms);
	dollarizing(ms->tokenlist);
	dollar_double(ms->tokenlist, envp);
	// free (command);
	return (ms->lex);
}
