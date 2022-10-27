/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:52:53 by kaheinz           #+#    #+#             */
/*   Updated: 2022/10/27 10:59:37 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**make_array_env(t_ms *ms)
{
	int		i;
	char	**env_array;
	char	*p;
	t_env	*tmp;

	env_array = ft_calloc(ms->env_lst_size + 1, sizeof(char *));
	tmp = ms->env_list;
	i = -1;
	while (++i < ms->env_lst_size)
	{
		p = ft_calloc(ft_strlen(tmp->content) + 1, sizeof(char));
		ft_strlcpy(p, tmp->content, ft_strlen(tmp->content) + 1);
		env_array[i] = p;
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	**make_array_token(t_ms *ms)
{
	int			i;
	char		**array;
	char		*p;
	t_ms_list	*tmp;

	array = ft_calloc(ft_tokenlistsize(ms->tokenlist) + 1, sizeof(char *));
	tmp = ms->tokenlist;
	i = -1;
	while (tmp->next && ms->current_section != tmp->section)
		tmp = tmp->next;
	while (++i < ft_tokenlistsize(ms->tokenlist))
	{
		p = ft_calloc(ft_strlen(tmp->token) + 1, sizeof(char));
		ft_strlcpy(p, tmp->token, ft_strlen(tmp->token) + 1);
		array[i] = p;
		if (!tmp || !tmp->next || tmp->section != tmp->next->section)
		{
			ms->current_section++;
			break ;
		}
		tmp = tmp->next;
	}
	array[i + 1] = NULL;
	return (array);
}

void	make_array(t_ms *ms, int nlines)
{
	int		i;
	char	**env_array;
	char	*p;
	t_env	*tmp;

	env_array = ft_calloc(nlines, sizeof(char *));
	tmp = ms->env_list;
	i = -1;
	while (++i < nlines)
	{
		p = ft_calloc(ft_strlen(tmp->content) + 1, sizeof(char));
		ft_strlcpy(p, tmp->content, ft_strlen(tmp->content) + 1);
		env_array[i] = p;
		tmp = tmp->next;
	}
	bubblesorting(nlines, env_array);
	i = -1;
	while (++i < nlines)
	{
		print_to_out(ms, "declare -x ");
		print_to_out(ms, env_array[i]);
		print_to_out(ms, "\n");
		free (env_array[i]);
	}
	free(env_array);
}

void	bubblesorting(int nlines, char *env_array[])
{
	int		x;
	int		y;
	char	*temp;

	x = 0;
	y = 0;
	while (x < nlines - 1)
	{
		y = x + 1;
		while (y < nlines)
		{
			if (ft_strncmp(env_array[x], env_array[y],
					ft_strlen(env_array[x])) > 0)
			{
				temp = env_array[x];
				env_array[x] = env_array[y];
				env_array[y] = temp;
			}		
			y++;
		}
		x++;
	}
}
