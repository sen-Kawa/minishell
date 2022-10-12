/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 17:58:39 by kaheinz          ###   ########.fr       */
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
	if (tmp && (ft_strncmp(tmp->token, "pwd\0", 4) == 0))
	{
		tmpenv = ms->env_list;
		while (tmpenv)
		{
			pwd_path = ft_strnstr(tmpenv->content, "PWD=", 4);
			if (pwd_path)
			{
				pwd_path = ft_substr(tmpenv->content, 5, 100);
				if (!pwd_path)
					return (0);
				ft_printf("%s\n", pwd_path);
				free (pwd_path);
				ms->exit_status = 0;
				return (1);
			}
			tmpenv = tmpenv->next;
		}
	}
	return (0);
}

int	b_cd(t_ms	*ms)
{
	t_ms_list	*tmp;
	t_env		*tmpenv;
	int			result;
	char		cwd[256];
	char		*del;

	tmp = ms->tokenlist;
	if (tmp)
	{
		result = ft_strncmp(tmp->token, "cd\0", 3);
		if (result == 0)
		{
			if (tmp->next)
			{
				if (!ft_strncmp(tmp->next->token, "~\0", 2))
				{
					del = tmp->next->token;
					tmp->next->token = getenv("HOME");
					free (del);
				}
				else if (!ft_strncmp(tmp->next->token, "~", 1))
				{
					del = tmp->next->token;
					tmp->next->token = ft_strjoin(getenv("HOME"), tmp->next->token + 1);
					free (del);
				}
				if (chdir(tmp->next->token))
				{
					ft_printf("cd : %s: No such file or diectory\n",
						tmp->next->token);
					ms->exit_status = 0;
					return (1);
				}
				else
				{
					tmpenv = ms->env_list;
					while (tmpenv)
					{
						if (ft_strnstr(tmpenv->content, "PWD=", 4))
						{
							if (getcwd(cwd, sizeof(cwd)) == NULL)
							{
								perror("getcwd() error");
								ft_printf("cd : %s: No such file or diectory\n",
									tmp->next->token);
								ms->exit_status = 0;
								return (1);
							}
							else
							{
								tmpenv->content = ft_strjoin("PWD=", &cwd[0]);
								ms->exit_status = 0;
								return (1);
							}
						}
						tmpenv = tmpenv->next;
					}
				}
			}
		}
	}
	return (0);
}
