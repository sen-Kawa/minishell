/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/13 16:40:07 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	b_echo(t_ms	*ms)
{
	t_ms_list	*tmp;
	int			flag;
	char		**token_array;

	flag = 1;
	tmp = ms->tokenlist;
	if (!tmp || ft_strncmp(tmp->token, "echo\0", 5) != 0)
		return (0);
	token_array = make_array_token(ms);
	if (tmp && tmp->next)
	{
		tmp = tmp->next;
		while (tmp && !ft_strncmp(tmp->token, "-n\0", 3))
		{
			flag++;
			tmp = tmp->next;
		}
	}
	else
	{
		print_to_out(ms, "\n");
		ms->exit_status = 0;
		return (1);
	}
	b_echo_print(token_array, ms, flag);
	ms->exit_status = 0;
	return (1);
}

void	b_echo_print(char **token_array, t_ms *ms, int flag)
{
	int	i;

	i = flag;
	while (token_array[i])
	{
		print_to_out(ms, token_array[i]);
		if (token_array[i + 1])
			print_to_out(ms, " ");
		if (token_array[i + 1] == NULL && flag == 1)
			print_to_out(ms, "\n");
		i++;
	}
}
