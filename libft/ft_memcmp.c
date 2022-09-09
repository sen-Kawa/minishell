/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:17:10 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:28:33 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The memcmp() function compares byte string s1 against byte string s2.
Both strings are assumed to be n bytes long.

RETURN
The memcmp() function returns zero if the two strings are identical,
otherwise returns the difference between the first two differing
bytes (treated as unsigned char values, so that `\200' is greater
than `\0', for example).  Zero-length strings are always identical.
This behavior is not required by C and portable code should only
depend on the sign of the returned value.

PARAMETERS
s1: The string to be trimmed.
set: The reference set of characters to trim.

EXTERNAL FUNCTIONS
malloc
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_char;
	unsigned char	*s2_char;

	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	if (s1 == s2)
		return (0);
	while (n > 0)
	{
		if (*s1_char != *s2_char)
			return (*s1_char - *s2_char);
		n--;
		s1_char++;
		s2_char++;
	}
	return (0);
}
