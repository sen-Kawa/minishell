/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:35:02 by ksura             #+#    #+#             */
/*   Updated: 2022/10/05 16:40:01 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <errno.h>

static char	*get_paths(int i, char **envp)
{
	char	*envp_path;

	while (envp[i])
	{
		envp_path = ft_strnstr(envp[i], "PATH=", 5);
		if (envp_path)
		{
			envp_path = ft_substr(envp[i], 5, 100);
			if (!envp_path)
				return (0);
			break ;
		}
		i++;
	}
	return (envp_path);
}

char	**slash_path(int i, char **paths)
{
	char	*tmp;

	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	return (paths);
}

char	*wright_path(int i, char **paths, char *cmd)
{
	char	*cmd_path;

	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free (cmd_path);
		i++;
	}
	return (NULL);
}

static void	print_error(char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL)
	{
		ft_putstr_fd("ksh: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("ksh: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	return ;
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*envp_path;
	char	*cmd_path;
	char	**paths;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (get_paths(i, envp) == 0)
		return (0);
	envp_path = get_paths(i, envp);
	paths = ft_split(envp_path, ':');
	if (!paths)
		return (0);
	i = 0;
	paths = slash_path(i, paths);
	i = 0;
	cmd_path = wright_path(i, paths, cmd);
	if (cmd_path != NULL)
		return (cmd_path);
	print_error(cmd);
	return (0);
}
