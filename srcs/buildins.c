/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/10 15:26:13 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	b_exit(t_ms	*ms)
{
	int		i;
	t_ms_list	*tmp;
	int		result;

	tmp = ms->tokenlist;
	if (!tmp)
		return (0);
	result = ft_strncmp(tmp->token, "exit\0", 4);
	if (result == 0 && tmp->next == NULL)
		exit (0);
	else if (result == 0 && tmp->next != NULL)
	{
		i = 0;
		while (tmp->next->token[i])
		{
			if (ft_isdigit(tmp->next->token[i]))
				i++;
			else
			{
				ft_printf("ksh: exit: %s: numeric argument required\n", tmp->next->token);
				exit(2);
			}
		}
		if (tmp->next->next != NULL)
		{
			ft_printf("ksh: exit: too many arguments\n");
			ms->exit_status = 127;
			return (1);
		}
		else
			exit (ft_atoi(tmp->next->token));
	}
	return (0);
}


int	b_env(char *token, t_ms *ms)
{
	int		result;
	t_env	*tmp;

	tmp = ms->env_list;
	if (!token)
		return (0);
	result = ft_strncmp(token, "env\0", 4);
	if (result == 0)
	{
		while (tmp)
		{
			ft_printf("%s\n", tmp->content);
			tmp = tmp->next;
		}
		ms->exit_status = 0;
		return (1);
	}
	return (0);
}

int	b_export(t_ms	*ms)
{
	int			result;
	int			flag;
	t_ms_list	*tmp;
	t_env		*new;
	char *copy;
	t_env		*tmp_env;
	char 		**splitted;
	// t_env		*tmp_env_pre;
	
	flag = 0;
	tmp = ms->tokenlist;
	if (!tmp)
		return (0);
	result = ft_strncmp(tmp->token, "export\0", 7);
	if (result == 0 && tmp->next == NULL)
	{
		make_array(ms, ms->env_lst_size);
		ms->exit_status = 0;
		return (1);
	}
	while (tmp)
	{
		if (result == 0 && ft_strchr(tmp->token, '='))
		{
			copy = ft_strdup(tmp->token);
			splitted = ft_split(copy, '=');
			tmp_env = ms->env_list;
			while (tmp_env && tmp_env->next && ft_strncmp(tmp->token, tmp_env->content, ft_strlen(splitted[0])))
				tmp_env = tmp_env->next;
			if (!ft_strncmp(tmp->token, tmp_env->content, ft_strlen(splitted[0])))
			{
				tmp_env->content = tmp->token;
				flag++;
			}
			else
			{
				new = ft_envvnew(tmp->token);
				ft_envvadd_back(&ms->env_list, new);
				ms->env_lst_size++;
				flag++;
			}
//			free(copy);
			free(splitted);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (flag > 0)
	{
		ms->exit_status = 0;
		return (1);
	}
	else
		return (0);
}

int	b_unset(t_ms	*ms)
{
	t_ms_list	*tmp;
	t_env		*envlst;
	t_env		*prev_envlst;

	tmp = ms->tokenlist;
	if (!tmp)
		return (0);
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
	//	if (!envlst->next)
	//		return (1);
		if (ft_strncmp(tmp->token, envlst->content,
				ft_strlen(tmp->token)) == 0 && !ft_strchr(tmp->token, '='))
		{
			prev_envlst->next = envlst->next;
			free (envlst);
			ms->env_lst_size--;
			ms->exit_status = 0;
			return (1);
		}
	}
	else if (ft_strncmp(tmp->token, "unset", 5) == 0 && tmp->next == NULL)
	{
		ms->exit_status = 0;
		return (1);
	}
	return (0);
}

void	print_to_out(t_ms *ms, char *to_print)
{
	int fd;
	
	if (ms->pipes_struct->fd_file[1] != -1)
		fd = ms->pipes_struct->fd_file[1];
	else 
		fd = 1;
	ft_putstr_fd(to_print, fd);
}

int	b_echo(t_ms	*ms)
{
	t_ms_list	*tmp;
	int			flag;

	flag = 0;
	tmp = ms->tokenlist;
	if (tmp)
	{
		if (ft_strncmp(tmp->token, "echo\0", 5) != 0)
			return (0);
	}
	else
		tmp = NULL;
	if (tmp->next)
	{
		tmp = tmp->next;
		if (!ft_strncmp(tmp->token, "-n\0", 3))
		{
			flag++;
			tmp = tmp->next;
		}
	}
	else
	{
		print_to_out(ms, "\n");
		tmp = tmp->next;
	}
	while(tmp)
	{
		print_to_out(ms, tmp->token);
		if (tmp->next)
			print_to_out(ms, " ");
		if (tmp->next == NULL && flag == 0)
			print_to_out(ms, "\n");
		tmp = tmp->next;
	}
	ms->exit_status = 0;
	return (1);
}
