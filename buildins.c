/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/09/26 14:31:34 by kaheinz          ###   ########.fr       */
/*   Updated: 2022/09/22 19:32:44 by ksura            ###   ########.fr       */
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

int	b_env(char *token, t_ms *ms)
{
	int		result;
	t_env	*tmp;

	tmp = ms->env_list;
	result = ft_strncmp(token, "env\0", 4);
	if (result == 0)
	{
		while (tmp)
		{
			ft_printf("%s\n", tmp->content);
			tmp = tmp->next;
		}
		return (1);
	}
	return (0);
}

void	b_export(t_ms	*ms)
{
	int			result;
	t_ms_list	*tmp;
	t_env		*new;

	tmp = ms->tokenlist;
	while (tmp)
	{
		result = ft_strncmp(tmp->token, "export\0", 7);
		if (result == 0 && tmp->next != NULL)
		{
			if (ft_strchr(tmp->next->token, '='))
			{
				new = ft_envvnew(tmp->next->token);
				ft_envvadd_back(&ms->env_list, new);
				ms->env_lst_size++;
			}
		}
		else if (result == 0 && tmp->next == NULL)
			make_array(ms, ms->env_lst_size);
		tmp = tmp->next;
	}
}

void	b_unset(t_ms	*ms)
{
	t_ms_list	*tmp;
	t_env		*envlst;
	t_env		*prev_envlst;

	tmp = ms->tokenlist;
	envlst = ms->env_list;
	if (ft_strncmp(tmp->token, "unset", 5) == 0 && tmp->next != NULL)
	{
		tmp = tmp->next;
		while (envlst && envlst->next && ft_strncmp(tmp->token,
				envlst->content, ft_strlen(tmp->token)) != 0)
		{
			prev_envlst = envlst;
			envlst = envlst->next;
		}
		if (ft_strncmp(tmp->token, envlst->content,
				ft_strlen(tmp->token)) == 0 && !ft_strchr(tmp->token, '='))
		{
			prev_envlst->next = envlst->next;
			free (envlst);
			ms->env_lst_size--;
		}
	}
}

/*
DESCRIPTION
The b_pwd() function returns the absolut working path to the standard output.


RETURN
0: no pwd was found
1: pwd was found and written to standard out

PARAMETER
token: char pointer of the toekn value
envp: char double pointer to environment variables
*/
int	b_pwd(char *token, char **envp)
{
	char	*pwd_path;
	int		result;
	int		i;

	result = ft_strncmp(token, "pwd\0", 4);
	if (result == 0)
	{
		i = 0;
		while (envp[i])
		{
			pwd_path = ft_strnstr(envp[i], "PWD=", 4);
			if (pwd_path)
			{
				pwd_path = ft_substr(envp[i], 5, 100);
				if (!pwd_path)
					return (0);
				ft_printf("%s\n", pwd_path);
				free (pwd_path);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

// int b_cd(t_ms	*ms, char **envp)
// {
// 	t_ms_list	*tmp;
// 	int		result;
// 	int		i;

// 	tmp = ms->tokenlist;
// 	while(tmp)
// 	{
// 		result = ft_strncmp(tmp->token, "cd\0", 3);
// 		if (result == 0)
// 		{
// 			if (ft_strncmp(tmp->next->token, "-n\0", 3) == 0)
// 			{
// 			}
// 			if (!chdir(tmp->next->token))
// 				return ;
// 		}
// 		tmp = tmp->next;
// 	}
// }
