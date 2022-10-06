/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:52:53 by kaheinz           #+#    #+#             */
/*   Updated: 2022/10/06 14:14:25 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


char **make_array_env(t_ms *ms)
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
	env_array[i + 1] = NULL;
	return (env_array);
}


char **make_array_token(t_ms *ms)
{
	int		i;
	char	**token_array;
	char	*p;
	t_ms_list	*tmp;

	token_array = ft_calloc(ft_tokenlistsize(ms->tokenlist) + 1, sizeof(char *));
	tmp = ms->tokenlist;
	i = -1;
	while (++i < ft_tokenlistsize(ms->tokenlist))
	{
		p = ft_calloc(ft_strlen(tmp->token) + 1, sizeof(char));
		ft_strlcpy(p, tmp->token, ft_strlen(tmp->token) + 1);
		token_array[i] = p;
		// // ft_printf("%i\n", tmp->section);
		// if(tmp->next->section != (tmp->section))
		// {
		// 	ms->tokenlist = tmp->next;
		// 	break ;
		// }
		tmp = tmp->next;
		
	}
	token_array[i + 1] = NULL;
	// i = -1;
	// while (++i < ft_tokenlistsize(ms->tokenlist))
	// 	ft_printf("token %s\n", token_array[i]);
	return (token_array);
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
