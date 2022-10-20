/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/20 18:41:17 by kaheinz          ###   ########.fr       */
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
		free(temp->token);
		free(temp);
	}
}

void	freeing_all(t_ms *ms, char *command)
{
	t_env	*tenv;

	freeing_tokens(ms);
	while (ms->env_list != NULL)
	{
		tenv = ms->env_list;
		ms->env_list = ms->env_list->next;
		free(tenv);
	}
	free (command);
	free (ms->pipes_struct);
	free (ms->lex);
	free (ms);
}

void	freeing_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
	{
			free(paths[i]);
			i++;
	}
	free (paths);
}

void	free_status(char *status, char *replaced, char *remain, char *sub)
{
	free(status);
	free(replaced);
	free(remain);
	free(sub);
}
