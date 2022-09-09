/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:16:14 by ksura             #+#    #+#             */
/*   Updated: 2022/07/05 10:25:32 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Adds the node ’new’ at the beginning of the list.

RETURN
-

PARAMETERS
lst: The address of a pointer to the first link of
a list.
new: The address of a pointer to the node to be
added to the list. 

EXTERNAL FUNCTIONS
-
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_stackadd_front(t_stack **stk, t_stack *new)
{
	new->next = *stk;
	*stk = new;
}
