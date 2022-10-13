/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:18 by ksura             #+#    #+#             */
/*   Updated: 2022/10/13 18:58:40 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	b_echo(t_ms	*ms)
{
	t_ms_list	*tmp;
	int			flag;

	write(1, "echo\n", 4);
	flag = 0;
	tmp = ms->tokenlist;
	if (!tmp || ft_strncmp(tmp->token, "echo\0", 5) != 0)
		return (0);
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
		tmp = tmp->next;
	}
	b_echo_print(tmp, ms, flag);
	ms->exit_status = 0;
	return (1);
}

void	b_echo_print(t_ms_list *tmp, t_ms *ms, int flag)
{
	while (tmp && tmp->section <= ms->current_section)
	{
		print_to_out(ms, tmp->token);
		if (tmp->next)
			print_to_out(ms, " ");
		if (tmp->next == NULL && flag == 0)
			print_to_out(ms, "\n");
		tmp = tmp->next;
	}
}
