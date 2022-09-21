/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/09/21 15:39:27 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	b_exit(char *command)
{
	int		i;
	char	*needle;

	i = 0;
	while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'))
		i++;
	needle = ft_strnstr(&command[i], "exit", 5);
	if (!needle)
		return ;
	else if (needle[4] == ' ' || needle[4] == '\0')
		exit(EXIT_SUCCESS);
}

int	b_env(char *token, char **envp)
{
	int i;
	int	result;

	result = ft_strncmp(token, "env\0", 4);
	if (result == 0)
	{
		i = 0;
		while (envp[i])
		{
			ft_printf("%s\n", envp[i]);
			i++;
		}
		
	 return (1);
	}
	return (0);
}

// int	b_export(t_lex_struct	*lex, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while(envp[i])
// 	{
// 		ms->lex->env_list->content
// 	}
	
// }

// void	initms(t_ms *ms)
// {
// 	ms = malloc(sizeof(t_ms));
// }