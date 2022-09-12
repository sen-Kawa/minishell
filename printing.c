/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:31:23 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 20:11:35 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    printing_tokens(t_ms_list *tokens)
{
        while (tokens)                                                          
        {
                ft_printf("Token: %s    Type: %s\n", tokens->token, tokens->type);
                tokens = tokens->next;
        }   
        ft_printf("___\n");
        ft_printf(" Token \n");
}