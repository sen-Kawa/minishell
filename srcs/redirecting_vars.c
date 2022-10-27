/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:54:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/27 09:37:04 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	delete_token(t_ms *ms);
void	freeing_prev(t_ms *ms, t_ms_list	*tmp_prev, t_ms_list	*tmp);

char	*get_vars(char **envp, char *var)
{
	char	*envp_var;
	char	*tmp;
	int		i;
	int		len_var;
	int		len_sub;

	tmp = ft_strjoin(var, "=");
	len_var = ft_strlen(tmp);
	i = 0;
	while (envp[i])
	{
		envp_var = ft_strnstr(envp[i], tmp, len_var);
		if (envp_var)
		{
			len_sub = ft_strlen(envp_var) - len_var;
			envp_var = ft_substr(envp[i], len_var, len_sub);
			if (!envp_var)
				return (0);
			break ;
		}
		i++;
	}
	free (tmp);
	return (envp_var);
}

void	delete_token(t_ms *ms)
{
	t_ms_list	*tmp;
	t_ms_list	*tmp_prev;

	tmp = ms->tokenlist;
	tmp_prev = ms->tokenlist;
	freeing_prev(ms, tmp_prev, tmp);
}

void	freeing_node(t_ms_list *tmp)
{
	free(tmp->token);
	free(tmp);
}

void	freeing_prev(t_ms *ms, t_ms_list *tmp_prev, t_ms_list *tmp)
{
	if (!tmp)
		return ;
	if (!ft_strncmp(tmp->type, "delete", 6))
	{
		if (tmp_prev == tmp)
		{
			ms->tokenlist = ms->tokenlist->next;
			tmp = tmp->next;
			freeing_node(tmp_prev);
			tmp_prev = tmp;
		}
		else
		{
			tmp_prev->next = tmp_prev->next->next;
			freeing_node(tmp);
			tmp = tmp_prev->next;
		}
	}
	else
	{
		tmp_prev = tmp;
		tmp = tmp->next;
	}
	freeing_prev(ms, tmp_prev, tmp);
}
