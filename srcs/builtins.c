/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/15 09:43:36 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	b_exit(t_ms	*ms)
{
	t_ms_list	*tmp;

	tmp = ms->tokenlist;
	if (!tmp || ft_strncmp(tmp->token, "exit\0", 4) != 0)
		return (0);
	if (tmp->next == NULL)
		exit (0);
	else if (tmp->next != NULL)
	{
		b_exit_arg(tmp->next->token);
		if (tmp->next->next != NULL)
		{
			ft_printf("ksh: exit: too many arguments\n");
			ms->exit_status = 127;
		}
		else
			exit (ft_atoi(tmp->next->token));
	}
	return (1);
}

void	b_exit_arg(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_isdigit(token[i]))
			i++;
		else
		{
			ft_printf("ksh: exit: %s: numeric argument required\n", token);
			exit(2);
		}
	}
}

int	b_env(t_ms *ms)
{
	t_ms_list	*tmp_tok;
	t_env		*tmp;

	tmp_tok = ms->tokenlist;
	tmp = ms->env_list;
	if (!tmp_tok || ft_strncmp(tmp_tok->token, "env\0", 4) != 0)
		return (0);
	if (tmp_tok->next && tmp_tok->next->section == ms->current_section)
	{
		print_to_out(ms, "env: No such file or directory");
		print_to_out(ms, "\n");
		ms->exit_status = 127;
	}
	else if (!tmp_tok->next
		|| (tmp_tok->next && tmp_tok->next->section != ms->current_section))
	{
		while (tmp)
		{
			print_to_out(ms, tmp->content);
			print_to_out(ms, "\n");
			tmp = tmp->next;
		}
		ms->exit_status = 0;
	}
	return (1);
}

int	b_unset(t_ms	*ms)
{
	t_ms_list	*tmp;
	t_env		*envlst;
	t_env		*prev_envlst;

	tmp = ms->tokenlist;
	envlst = ms->env_list;
	if (!tmp || ft_strncmp(tmp->token, "unset", 5) != 0)
		return (0);
	printf("unset\n");
	if (tmp->next != NULL && tmp->next->section == ms->current_section)
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
			modify_env_list(prev_envlst, envlst, ms);
	}
	ms->exit_status = 0;
	return (1);
}

void	modify_env_list(t_env *prev_envlst, t_env *envlst, t_ms *ms)
{
	prev_envlst->next = envlst->next;
	free (envlst);
	ms->env_lst_size--;
}
