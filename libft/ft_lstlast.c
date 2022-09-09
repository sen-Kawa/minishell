/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:53:06 by ksura             #+#    #+#             */
/*   Updated: 2022/07/05 10:25:02 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Returns the last node of the list.

RETURN
Last node of the list

PARAMETERS
lst: The beginning of the list.

EXTERNAL FUNCTIONS
-
*/
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_stack	*ft_stacklast(t_stack *stk)
{
	t_stack	*last;

	if (!stk)
		return (NULL);
	last = stk;
	while (last->next != NULL)
		last = last->next;
	return (last);
}
