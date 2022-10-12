/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 19:09:47 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
DESCRIPTION
PartIV of redirecting().
Alters types of tokens for redirection purposes.

RETURN
-

PARAMETERS
tmp: linked list for tokens

EXTERNAL FUNCTIONS
-
*/
int	redir2_1_1(t_ms_list *tmp, t_ms *ms, int outfd)
{
	if (!tmp->token[2])
	{
		if (tmp->next)
		{
			tmp->next->type = "delete";
			if ((access (tmp->next->token, F_OK) == 0)
				&& (access (tmp->next->token, W_OK) != 0))
			{
				ft_printf("ksh: %s: Permission denied\n", \
				tmp->next->token);
				ms->exit_status = 1;
				ms->lex->error = 1;
				return (1);
			}
		}
		ms->pipes_struct->fd_file[outfd] = open(tmp->next->token, \
		O_RDWR | O_APPEND | O_CREAT);
	}
	return (0);
}

/*
DESCRIPTION
PartIII of redirecting().
Alters types of tokens for redirection purposes.

RETURN
-

PARAMETERS
tmp: linked list for tokens

EXTERNAL FUNCTIONS
-
*/
void	redir2_1(t_ms_list *tmp, t_ms *ms, int outfd)
{
	if (tmp->token[0] && tmp->token[1])
	{
		if (tmp->token[0] == '>' && tmp->token[1] == '>')
		{
			tmp->type = "delete";
			if (redir2_1_1(tmp, ms, outfd) == 1)
				return ;
			else if (tmp->token[2] != '\0')
			{
				tmp->type = "delete";
				if ((access (tmp->token + 2, F_OK) == 0)
					&& (access (tmp->token + 2, W_OK) != 0))
				{
					ft_printf("ksh: %s: Permission denied\n", tmp->token + 2);
					ms->exit_status = 1;
					ms->lex->error = 1;
					return ;
				}
				ms->pipes_struct->fd_file[outfd] = open(tmp->token + 2, \
				O_RDWR | O_APPEND | O_CREAT);
			}
		}
	}
}

/*
DESCRIPTION
PartII of redirecting().
Alters types of tokens for redirection purposes.

RETURN
-

PARAMETERS
tmp: linked list for tokens

EXTERNAL FUNCTIONS
-
*/
void	redir2(t_ms_list *tmp, t_ms	*ms, int outfd)
{
	if (tmp->token[0] == '<' && tmp->token[1] == '<')
	{
		if (tmp->token[2] != '\0')
		{
			tmp->type = "delete";
			heredoc(ms, tmp->token + 2);
		}
		else if (tmp->token[2] == '\0')
		{
			tmp->type = "delete";
			if (tmp->next)
			{
				tmp->next->type = "delete";
				heredoc(ms, tmp->next->token);
			}
		}
	}
	redir2_1(tmp, ms, outfd);
}

/*
DESCRIPTION
Alters types of tokens for redirection purposes.
- "<" chagens type of following node to "infile"
- ">" chagens type of following node to "outfile"
- "<<*" chagens type of node to "heredoc"
- ">>" chagens type of following node to "app_outfile"

RETURN
-

PARAMETERS
tokens: linked list for tokens

EXTERNAL FUNCTIONS
-
*/
void	redirecting(t_ms *ms)
{
	t_ms_list	*tmp;
	int			infd;
	int			outfd;

	infd = 0;
	outfd = 1;
	tmp = ms->tokenlist;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->section == ms->current_section)
			{
				if (redir1_0(tmp, ms, infd, outfd) == 1)
					return ;
				redir2(tmp, ms, outfd);
			}
			tmp = tmp->next;
		}
		delete_token(ms);
	}
}
