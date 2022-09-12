/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 18:23:57 by ksura            ###   ########.fr       */
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
	printf("The Length is:%i\n", length);
	while (command[start] == ' ')
		start++;
	while(command[start + i] && *command)
	{
	
		
		if (start + i <= length)
		{
			if (command[start + i] == ' ')
			{
				write(1, "inside 1\n", 10);
				if (i > 0)
				{
					part = ft_substr(command, start, i);
					newbe = ft_tokennew(part, "space");
					ft_tokenadd_back(&tokens, newbe);
				}
				while (command[start + i] == ' ')
					i++;
				start = start + i;
				i = -1;
			}
		}
		
		i++;
		if (command[start + i] == '"')
		{
			write(1, "Quote\n", 7);
			i++;
			while (command[start + i] != '"')
				i++;
			
			part = ft_substr(command, start + 1, i - 1);
			newbe = ft_tokennew(part, "double quotes");
			ft_tokenadd_back(&tokens, newbe);
			i++;
			start = start + i;
			i = 0;
		}
		
	}
	if (i > 0)
	{
		write(1, "inside 2\n", 10);
		part = ft_substr(command, start, i);
		newbe = ft_tokennew(part, "space_before");
		// free(part);
		ft_tokenadd_back(&tokens, newbe);
	}
	
}
