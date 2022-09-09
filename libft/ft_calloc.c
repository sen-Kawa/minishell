/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:05:56 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:27:22 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The calloc() function contiguously allocates enough space 
for count objects that are size bytes of memory each and 
returns a pointer to the allocated memory.  The allo-
cated memory is filled with bytes of value zero.

RETURN
If successful, calloc(), malloc(), realloc(), reallocf(), valloc(), and
aligned_alloc() functions return a pointer to allocated memory.  
If there is an error, they return a NULL pointer and set errno to ENOMEM.

PARAMETERS
count: Number of Objects.
size: Size of the objects.

EXTERNAL FUNCTIONS
malloc, ft_bzero
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	else if (count >= __SIZE_MAX__ || size >= __SIZE_MAX__)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
//     int* allocated_with_malloc = malloc(10 * sizeof(int));
//     char* allocated_with_calloc = calloc(10, sizeof(char));
//     printf("Values of allocated_with_calloc: ");
//     for (size_t i = 0; i < 10; ++i) {
//         printf("%d ", allocated_with_calloc[i]);}
//     putchar('\n');
// 	    int* allocated_with_ft_calloc = ft_calloc(10, sizeof(int));
//     printf("Values of allocated_with_ft_calloc: ");
//     for (size_t i = 0; i < 10; ++i) {
//         printf("%d ", allocated_with_ft_calloc[i]);
//     }
//     putchar('\n');
//     // Remember to always free dynamically allocated memory.
//     free(allocated_with_malloc);
//     free(allocated_with_calloc);
// 	free(allocated_with_ft_calloc);
// }