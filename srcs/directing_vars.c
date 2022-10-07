/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directing_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/07 19:37:35 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	delete_token(t_ms *ms);

static char	*get_vars(char **envp, char *var)
{
	char	*envp_var;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(var, "=");
	i = 0;
	while (envp[i])
	{
		envp_var = ft_strnstr(envp[i], tmp, ft_strlen(var) + 1);
		if (envp_var)
		{
			envp_var = ft_substr(envp[i], ft_strlen(var) + 1, 100);
			if (!envp_var)
				return (0);
			break ;
		}
		i++;
	}
	free (var);
	free (tmp);
	return (envp_var);
}

char	*replacing_vars(char **envp, int ds, char **dollar_split, char *new_dollar)
{
	char	*var;

	//printf("Dollar split at ds %s\n", dollar_split[ds]);
	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
		var = "";
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
//	free (dollar_split[ds]);
	dollar_split[ds] = var;
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
	new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
	// free(dollar_split[ds]);
	return (new_dollar);
}

char	*replacing_vars_middle_dollar(char **envp, int ds, char **dollar_split, char *new_dollar)
{
	char	*var;
	
	var = get_vars(envp, dollar_split[ds]);
	if (var == NULL)
		var = "";
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
//	free (dollar_split[ds]);
	dollar_split[ds] = var;
	// printf("\tdstring %i.%i: %s is %s\n", i, ds, dollar_split[ds], var);
	if (ds == 1)
	{
		new_dollar = ft_strjoin(dollar_split[0], dollar_split[1]);
		free (dollar_split[0]);
		free (dollar_split[1]);
		write(1, "here", 4);
	}
	else
	{
		new_dollar = ft_strjoin(new_dollar, dollar_split[ds]);
		free (dollar_split[ds]);
		write(1, "here", 4);
	}
	return (new_dollar);
}
/*
DESCRIPTION
PartII of redirecting().
Alters types of tokens for redirection purposes.
In case of << it gives types to the symbol and
the delimiter but doesn't split them if they are together

RETURN
-

PARAMETERS
tmp: linked list for tokens

EXTERNAL FUNCTIONS
-
*/
void	redir2(t_ms_list *tmp, t_ms	*ms)
{
	if (tmp->token[0] == '<' && tmp->token[1] == '<')
	{
		if (tmp->token[2] != '\0')
			tmp->type = "sym+delim";
		else if (tmp->token[2] == '\0')
		{
			tmp->type = "heredoc_sym";
			if (tmp->next)
				tmp->next->type = "delim";
		}
	}
	if (tmp->token[0] && tmp->token[1] && !tmp->token[2])
	{
		if (tmp->token[0] == '>' && tmp->token[1] == '>')
		{
			tmp->type = "delete";
			if (tmp->token[2] == '\0')
			{
				if (tmp->next)
				{
					tmp->next->type = "delete";
					if ((access (tmp->next->token, F_OK) == 0)
						&& (access (tmp->next->token, W_OK) != 0))
					{
						ft_printf("ksh: %s: Permission denied\n", tmp->next->token);
						ms->exit_status = 1;
						ms->lex->error = 1;
						return ;
					}
				}
				ms->pipes_struct->fd_file[1] = open(tmp->next->token, O_RDWR | O_APPEND | O_CREAT);
			}
			else if (tmp->token[2] != '\0')
			{
				if ((access (tmp->token + 2, F_OK) == 0)
					&& (access (tmp->token + 2, W_OK) != 0))
				{
					ft_printf("ksh: %s: Permission denied\n", tmp->token + 2);
					ms->exit_status = 1;
					ms->lex->error = 1;
					return ;
				}
				ms->pipes_struct->fd_file[1] = open(tmp->token + 2, O_RDWR | O_APPEND | O_CREAT);
			}
		}
	}
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

	tmp = ms->tokenlist;
	if (tmp)
	{
		while (tmp)
		{
			if (!ft_strncmp(tmp->type, "double quotes\0", 15) 
			|| !ft_strncmp(tmp->type, "single quotes\0", 15))
				break;
			if (tmp->token[0] == '<' && !tmp->token[1])
			{
				tmp->type = "delete";
				if (tmp->next)
				{
					tmp->next->type = "delete";
					ms->pipes_struct->fd_file[0] = open(tmp->next->token, O_RDONLY);
					if (ms->pipes_struct->fd_file[0] == -1)
					{
						ft_printf("ksh: %s: No such file or directory\n", tmp->next->token);
						ms->exit_status = 1;
						ms->lex->error = 1;
						return ;
					}

				}
			}
			else if (tmp->token[0] == '>' && !tmp->token[1])
			{
				tmp->type = "delete";
				if (tmp->next)
				{
					tmp->next->type = "delete";
					if ((access (tmp->next->token, F_OK) == 0)
									&& (access (tmp->next->token, W_OK) != 0))
					{
						ft_printf("ksh: %s: Permission denied\n", tmp->next->token);
						ms->exit_status = 1;
						ms->lex->error = 1;
						return ;
					}
					ms->pipes_struct->fd_file[1] = open(tmp->next->token,  O_WRONLY | O_CREAT);
				}
			}
			redir2(tmp, ms);
			tmp = tmp->next;
		}
		delete_token(ms);
	}
}

void	delete_token(t_ms *ms)
{
	t_ms_list	*tmp;
	t_ms_list	*tmp_prev;


	tmp = ms->tokenlist;
	tmp_prev = ms->tokenlist;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "delete", 6))
		{
				if (tmp_prev == tmp)
				{
					ms->tokenlist = ms->tokenlist->next;
					tmp = tmp->next;
					free(tmp_prev);
					tmp_prev = tmp;
				}
				else
				{
					tmp_prev->next = tmp_prev->next->next;
					free (tmp);
					tmp = tmp_prev->next;
				}
		}
		else
		{
			tmp_prev = tmp;
			tmp = tmp->next;
		}
	}
}
