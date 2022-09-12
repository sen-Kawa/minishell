/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:31:23 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 11:45:44 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printing_list_a(t_ms_list *tokens)
{
        while (tokens)                                                          
        {
                ft_printf("Node: %s\n", tokens->token);
                tokens = tokens->next;
        }   
        ft_printf("___\n");
        ft_printf(" Token \n");
}