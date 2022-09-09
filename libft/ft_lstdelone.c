/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:15:03 by ksura             #+#    #+#             */
/*   Updated: 2022/06/07 14:16:30 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given
as a parameter and free the node. The memory of
’next’ must not be freed.

RETURN
-

PARAMETERS
lst: The node to free.
del: The address of the function used to delete
the content.

EXTERNAL FUNCTIONS
free
*/
void	ft_lstdelone(t_list *lst, void (*del)(int))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
