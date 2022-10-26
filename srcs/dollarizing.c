/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarizing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:09:43 by ksura             #+#    #+#             */
/*   Updated: 2022/10/26 20:29:24 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	dollarizing(t_ms *ms)
{
	int			i;
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (tmp)
	{
		while (tmp)
		{
			i = 0;
			while (tmp->token[i])
			{
				replacing_exit(ms, i, tmp);
				i++;
			}
			tmp = tmp->next;
		}
	}
}
