/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:59:22 by ksura             #+#    #+#             */
/*   Updated: 2022/07/05 10:23:29 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Adds the node ’new’ at the end of the list.

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
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		ft_lstlast(*lst)->next = new;
	}
}

void	ft_stackadd_back(t_stack **stk, t_stack *new)
{
	if (!*stk)
		*stk = new;
	else
	{
		ft_stacklast(*stk)->next = new;
	}
}
