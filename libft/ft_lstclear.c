/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:26:09 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 19:57:46 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Deletes and frees the given node and every
successor of that node, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL.

RETURN
-

PARAMETERS
lst: The address of a pointer to a node.
del: The address of the function used to delete
the content of the node.

EXTERNAL FUNCTIONS
free
*/
void	ft_lstclear(t_list **lst, void (*del)(int))
{
	t_list	*first;
	t_list	*second;

	if (*lst && lst && del)
	{
		first = *lst;
		while (first)
		{
			second = first->next;
			ft_lstdelone(first, del);
			first = second;
		}
		*lst = NULL;
	}
}
