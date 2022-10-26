/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/26 19:11:01 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	redir1_1(t_ms_list *tmp, t_ms *ms, int infd)
{
	tmp->type = "delete";
	if (tmp->next)
	{
		tmp->next->type = "delete";
		ms->pipes_struct->fd_file[infd] = \
		open(tmp->next->token, O_RDONLY);
		if (ms->pipes_struct->fd_file[infd] == -1)
		{
			ft_printf("ksh: %s: No such file or directory\n", \
			tmp->next->token);
			ms->exit_status = 1;
			ms->lex->error = 1;
			return (1);
		}
	}
	return (0);
}

int	redir1_2(t_ms_list *tmp, t_ms *ms, int infd)
{
	tmp->type = "delete";
	ms->pipes_struct->fd_file[infd] = open(tmp->token + 1, \
	O_RDONLY);
	if (ms->pipes_struct->fd_file[infd] == -1)
	{
		ft_printf("ksh: %s: No such file or directory\n", \
		tmp->token + 1);
		ms->exit_status = 1;
		ms->lex->error = 1;
		return (1);
	}
	return (0);
}

int	redir1_3(t_ms_list *tmp, t_ms *ms, int outfd)
{
	tmp->type = "delete";
	if (tmp->next)
	{
		tmp->next->type = "delete";
		if ((access (tmp->next->token, F_OK) == 0) \
		&& (access (tmp->next->token, W_OK) != 0))
		{
			ft_printf("ksh: %s: Permission denied\n", \
			tmp->next->token);
			ms->exit_status = 1;
			ms->lex->error = 1;
			return (1);
		}
		ms->pipes_struct->fd_file[outfd] = \
		open(tmp->next->token, O_WRONLY | O_CREAT, 0777);
	}
	return (0);
}

int	redir1_4(t_ms_list *tmp, t_ms *ms, int outfd)
{
	tmp->type = "delete";
	ms->pipes_struct->fd_file[outfd] = open(tmp->token + 1, \
	O_CREAT | O_WRONLY, 0777);
	if (ms->pipes_struct->fd_file[outfd] == -1)
	{
		ft_printf("ksh: %s: No such file or directory1\n", \
		tmp->token + 1);
		ms->exit_status = 1;
		ms->lex->error = 1;
		return (1);
	}
	return (0);
}

int	redir1_0(t_ms_list *tmp, t_ms *ms, int infd, int outfd)
{
	if (tmp->token == NULL)
		return (1);
	if (tmp->token[0] == '<' && !tmp->token[1])
	{
		if (redir1_1(tmp, ms, infd) == 1)
			return (1);
	}
	else if ((tmp->token[0] == '<' && tmp->token[1] \
	&& tmp->token[1] != '<'))
	{
		if (redir1_2(tmp, ms, infd) == 1)
			return (1);
	}
	else if (tmp->token[0] == '>' && !tmp->token[1])
	{
		if (redir1_3(tmp, ms, outfd) == 1)
			return (1);
	}
	else if ((tmp->token[0] == '>' && tmp->token[1] \
	&& tmp->token[1] != '>'))
	{
		if (redir1_4(tmp, ms, outfd) == 1)
			return (1);
	}
	return (0);
}
