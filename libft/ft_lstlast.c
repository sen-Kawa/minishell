/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:53:06 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 11:41:16 by ksura            ###   ########.fr       */
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

t_ms_list	*ft_tokenlast(t_ms_list *tokens)
{
	t_ms_list	*last;

	if (!tokens)
		return (NULL);
	last = tokens;
	while (last->next != NULL)
		last = last->next;
	return (last);
}