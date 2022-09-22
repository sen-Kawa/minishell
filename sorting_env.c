/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:52:53 by kaheinz           #+#    #+#             */
/*   Updated: 2022/09/22 12:02:51 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_array(t_ms *ms, int nlines)
{
	int		i;
	int		len;
	char	**env_array;
	char	*p;
	t_env	*tmp;

	env_array = ft_calloc(nlines, sizeof(char));
	tmp = ms->env_list;
	i = 0;
	len = 0;
	while (i < nlines)
	{
		len = ft_strlen(tmp->content);
		printf("CONTENT OF NODE : %s\n", tmp->content);
		p = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(p, tmp->content, len + 1);
		printf("CONTENT OF P : %s\n", p);
		env_array[i] = p;
		printf("CONTENT OF env array i %i : %s\n", i, env_array[i]);
		tmp = tmp->next;
		i++;
	}
	ft_printf("i is: %i\n", i);
		ft_printf("TEST %s\n", env_array[0]);
	bubblesorting(nlines, env_array);
	i = 0;
	while (i < nlines)
	{
		i++;
	}
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
