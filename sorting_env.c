/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:52:53 by kaheinz           #+#    #+#             */
/*   Updated: 2022/09/22 12:30:50 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_printf("declare -x %s\n", env_array[i]);
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
