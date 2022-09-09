/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:40:24 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:28:28 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The memchr() function locates the first occurrence of c
(converted to an unsigned char) in string s.

RETURN
The memchr() function returns a pointer to the byte
located, or NULL if no such byte exists within n bytes.

PARAMETERS

EXTERNAL FUNCTIONS

*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s_char;
	char	c_char;
	size_t	index;

	s_char = (char *)s;
	c_char = (char)c;
	index = 0;
	if (n == 0)
		return (0);
	while (*s_char != c_char && index < (n - 1))
	{
		s_char++;
		index++;
	}
	if (*s_char == c_char)
		return ((void *)s_char);
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     const char str[50] = {0, 1, 2 ,3 ,4 ,5};
// 	// int a = 'i';
// 	printf("%x\n", (unsigned int)ft_memchr(str, 0, 0));
// 	printf("%x\n", (unsigned int) memchr(str, 0, 0));
// }