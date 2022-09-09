/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 08:27:08 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:46 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The strnstr() function locates the first occurrence of the null-termi-
nated string needle in the string haystack, where not more than len char-
acters are searched.  Characters that appear after a `\0' character are
not searched.  Since the strnstr() function is a FreeBSD specific API, it
should only be used when portability is not a concern.

RETURN
If needle is an empty string, haystack is returned; if needle occurs
nowhere in haystack, NULL is returned; otherwise a pointer to the first
character of the first occurrence of needle is returned.

PARAMETERS
haystack: pointer to string IN which to search
needle: pointer to string to find in haystack
len: max len of haystack in which to search
EXTERNAL FUNCTIONS

*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		h_i;
	size_t		n_i;

	if (*needle == '\0')
		return ((char *)haystack);
	h_i = 0;
	while (haystack[h_i] != '\0' && h_i < len)
	{
		n_i = 0;
		while (haystack[h_i + n_i] == needle[n_i] && h_i + n_i < len)
		{
			if (needle[n_i + 1] == '\0')
				return ((char *)(haystack + h_i));
			n_i++;
		}
		h_i++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char str[] = "This is the Heystack";
// 	const char ne[] = "\0";
// 	printf("%s",ft_strnstr(str, ne, 15));
// }