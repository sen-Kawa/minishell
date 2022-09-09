/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:29:51 by ksura             #+#    #+#             */
/*   Updated: 2022/07/05 11:01:09 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL.

RETURN
The new node

PARAMETERS
content: The content to create the node with. 

EXTERNAL FUNCTIONS
malloc
*/
t_list	*ft_lstnew(int content)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof (t_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	new_list->chunk = 0;
	return (new_list);
}

t_stack	*ft_stacknew(int value)
{
	t_stack	*new_list;

	new_list = (t_stack *)ft_calloc(1, sizeof(t_stack));
	if (!new_list)
		return (NULL);
	new_list->value = value;
	new_list->next = NULL;
	return (new_list);
}
