/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:55:55 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:49 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The strrchr() function is identical to strchr(), except it locates the
last occurrence of c.

The strchr() function locates the first occurrence of c (converted to a
char) in the string pointed to by s.  The terminating null character is
considered to be part of the string; therefore if c is `\0', the func-
tions locate the terminating `\0'.

RETURN
The functions strchr() and strrchr() return a pointer to the located
character, or NULL if the character does not appear in the string.

PARAMETER
c: character to search for in s
s: pointer to str in which to look for c
*/
char	*ft_strrchr(const char *s, int c)
{
	char	c_char;
	int		index;

	c_char = (char)c;
	index = ft_strlen(s);
	while ((*(s + index) != c_char) && index > 0)
	{
		index--;
	}
	if (*(s + index) == c_char)
		return ((char *)(s + index));
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     const char str[50] = "What is ft_strrchr really doing?.";
// 	int a = '.';
// 	printf("%x\n", (unsigned int)ft_strrchr(str, a));
// 	printf("%x\n", (unsigned int) strrchr(str, a));
// }