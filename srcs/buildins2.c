/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/24 13:37:42 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
int	b_pwd(t_ms	*ms)
{
	char		*pwd_path;
	t_env		*tmpenv;
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (!tmp || (ft_strncmp(tmp->token, "pwd\0", 4) != 0))
		return (0);
	tmpenv = ms->env_list;
	while (tmpenv)
	{
		pwd_path = ft_strnstr(tmpenv->content, "PWD=", 4);
		if (pwd_path)
		{
			pwd_path = ft_substr(tmpenv->content, 5, 200);
			if (!pwd_path)
				return (0);
			print_to_out(ms, pwd_path);
			print_to_out(ms, "\n");
			free (pwd_path);
		}
		tmpenv = tmpenv->next;
	}
	ms->exit_status = 0;
	return (1);
}

int	b_cd(t_ms	*ms)
{
	t_ms_list	*tmp;
	int			i;

	i = 1;
	tmp = ms->tokenlist;
	if (!tmp || ft_strncmp(tmp->token, "cd\0", 3) != 0)
		return (0);
	if (!tmp->next)
		i = chdir(getenv("HOME"));
	else if (tmp->next)
	{
		b_cd_tilde(&tmp->next->token);
		i = chdir(tmp->next->token);
	}
	if (i == 0)
		update_pwd(ms);
	else if (i == -1)
		unsuccess_chdir(ms);
	return (1);
}

void	update_pwd(t_ms *ms)
{
	t_env		*tmpenv;
	char		cwd[256];
	char		*tmp;

	tmpenv = ms->env_list;
	while (tmpenv)
	{
		if (ft_strnstr(tmpenv->content, "PWD=", 4))
		{
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				perror("getcwd() error");
				ms->exit_status = 1;
			}
			else
			{
				tmp = tmpenv->content;
				tmpenv->content = ft_strjoin("PWD=", &cwd[0]);
				ms->exit_status = 0;
				free (tmp);
			}
		}
		tmpenv = tmpenv->next;
	}
}

void	b_cd_tilde(char **token)
{
	char *tmp;
	
	
	if (!ft_strncmp(*token, "~\0", 2))
	{
		tmp = *token;
		*token = ft_strdup(getenv("HOME"));
		free (tmp);
	}
	else if (!ft_strncmp(*token, "~", 1))
	{
		tmp = *token;
		*token = ft_strjoin(getenv("HOME"), &tmp[1]);
		free (tmp);
	}
}

void	unsuccess_chdir(t_ms *ms)
{
	ft_printf("cd : No such file or directory\n");
	ms->exit_status = 1;
}
