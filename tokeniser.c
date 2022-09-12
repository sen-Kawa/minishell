/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 11:57:04 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	tokenice(char *command, t_ms_list *tokens)
{
	int	i;
	int	length;
	int	start;
	char *part;
	t_ms_list	*newbe;
	
	i = 0;
	start = 0;
	length = ft_strlen(command);
	printf("The Length is:%i", length);
	while(command[start + i] && *command)
	{
		if (command[start + i] == ' ')
		{
			part = ft_substr(command, start, i);
			newbe = ft_tokennew(part, NULL);
			ft_tokenadd_back(&tokens, newbe);
			start = i + 1;
			i = -1;
			// printf("Yes");
			//check if there is a list
			// if yes lst_addback / no - new list
		}
		// printf("Yes");
		i++;
	}
}