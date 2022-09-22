/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/09/22 16:19:56 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_env	*ft_envvnew(char *content)
{
	t_env	*new_list;

	new_list = malloc(sizeof (t_env));
	if (!new_list)
		return (NULL);
	new_list->content= content;
	new_list->next = NULL;
	return (new_list);
}

t_env	*ft_envvlast(t_env *envv)
{
	t_env	*last;

	if (!envv)
		return (NULL);
	last = envv;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_envvadd_back(t_env **env, t_env *new)
{
	if (!*env)
		*env = new;
	else
	{
		ft_envvlast(*env)->next = new;
	}
}

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

int	b_env(t_ms *ms, char **envp)
{
	int i;
	int	result;
	t_ms	*tmp;
	t_env	*new;

	i = 0;
	if (!ms->env_list)
	{
		while(envp[i])
		{
			new = ft_envvnew(envp[i]);
			ft_envvadd_back(&ms->env_list, new);
			i++;
		}
	}
	tmp = ms;
	new = ms->env_list;
	while(tmp->tokenlist)
	{
		new = ms->env_list;
		result = ft_strncmp(tmp->tokenlist->token, "env\0", 4);
		if (result == 0)
		{
			i = 0;
			while (new)
			{
				ft_printf("%s\n", new->content);
				new = new->next;
			}
			return (1);
		}
		tmp->tokenlist = tmp->tokenlist->next;
	}
	
	return (0);
}

int	b_export(t_ms	*ms, char **envp)
{
	int	i;
	t_env	*new;
	int	result;
	t_ms_list	*tmp;
	
	i = 0;
	if (!ms->env_list)
	{
		while(envp[i])
		{
			new = ft_envvnew(envp[i]);
			ft_envvadd_back(&ms->env_list, new);
			i++;
		}
	}
	i = 0;
	new = ms->env_list;
	while(new)
		{
			i++;
			new = new->next;
		}
	tmp = ms->tokenlist;
	while(tmp)
	{
		result = ft_strncmp(tmp->token, "export\0", 7);
		if (result == 0 && tmp->next == NULL)
		{
			make_array(ms, i);
		}
			
		else if (result == 0 && tmp->next != NULL)
		{
			if (ft_strchr(tmp->next->token, '='))
			{
				new = ft_envvnew(tmp->next->token);
				ft_envvadd_back(&ms->env_list, new);
				i++;
			}
			else
				return (i);
		}
		tmp = tmp->next;
	}
	return (i);
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
				return (1) ;
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
