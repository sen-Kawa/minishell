/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:37:02 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:41 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The strncmp() function compares not more than n characters.
Because strncmp() is designed for comparing strings rather
than binary data, characters that appear after
a `\0' character are not compared.

RETURN
The strcmp() and strncmp() functions return an integer
greater than, equal to, or less than 0, according as
the string s1 is greater than, equal to, or less than the
string s2.  The comparison is done using unsigned characters,
so that `\200' is greater than `\0'.

PARAMETERS

EXTERNAL FUNCTIONS

*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				result;

	result = 0;
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < (n))
	{
		i++;
	}
	if (i == n)
		return (0);
	result = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (result);
}

// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	unsigned int	n = 10;
// 	char	str1[] = "String 4";
// 	char	str2[] = "String 2"; 
// 	printf("Vergleich str1 mit str2: %d \n", strncmp(str1, str2, n));
// 	printf("Vergleich str1 mit str2: %d \n", ft_strncmp(str1, str2, n));
// }