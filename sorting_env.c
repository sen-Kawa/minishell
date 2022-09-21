/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:52:53 by kaheinz           #+#    #+#             */
/*   Updated: 2022/09/21 19:38:00 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_array(t_ms *ms, int nlines)
{
	int		i;
	int		print_index;
	int		len;
	char		*env_array[nlines];
	char		*p;
	t_env	*tmp;

	tmp = ms->env_list;
	print_index = 0;
	i = 0;
	len = 0;
	while (i < nlines)
	{
		len = ft_strlen(tmp->content);
		p = ft_calloc(len, sizeof(char));
		ft_strlcpy(p, tmp->content, len);
		env_array[i] = p;
		tmp = tmp->next;
		i++;
	}
//	ft_printf("number of lines: %i", print_index);
//	ft_printf("number of i: %i", i);
	//sort here
	int x = 0;
	int y = 0;
	char	*temp;
	while (x < nlines - 1)
	{
		y = x + 1;
		while (y < nlines)
		{
			if (ft_strncmp(env_array[x], env_array[y], ft_strlen(env_array[x])) > 0)	
			{
				temp = env_array[x];
				env_array[x] = env_array[y];
				env_array[y] = temp;
			}		
			y++;
		}
	x++;
	}
	while (print_index < nlines)
	{
		ft_printf("declare -x %s\n", env_array[print_index]);
		print_index++;
	}
//	return (*env_array);
}
