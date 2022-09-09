/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:53:37 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:53 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.

RETURN
The trimmed string.
NULL if the allocation fails.

PARAMETERS
s1: The string to be trimmed.
set: The reference set of characters to trim.

EXTERNAL FUNCTIONS
malloc
*/
char		*ft_strtrim(char const *s1, char const *set);
static int	is_includet(char c1, const char	*set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*dst;
	size_t		ibe;
	size_t		iend;
	size_t		len;

	ibe = 0;
	if (!s1)
		return (NULL);
	if (!set || !*s1)
		return (ft_strdup(s1));
	while (is_includet(s1[ibe], set) && s1[ibe])
		ibe++;
	iend = ft_strlen(s1) - 1;
	if (ibe > iend)
		return (ft_strdup(""));
	while (is_includet(s1[iend], set) && iend > ibe)
		iend--;
	len = iend - ibe + 1;
	dst = ft_substr(s1, ibe, len);
	if (!dst)
		return (NULL);
	return (dst);
}

static int	is_includet(char c1, const char	*set)
{
	while (*set)
	{
		if (c1 == *set)
			return (1);
		set++;
	}
	return (0);
}
// #include <stdio.h>
// int main()
// {	
// 	char * s = ft_strtrim("+++++-+HEyHEy_", "+_-Hy");
// 	printf("the string is: %s\n", s);
// 	free(s);
// 	char * a = ft_strtrim("", "-_");
// 	printf("the string is: %s\n", a);
// 	free(a);
// 	char * b = ft_strtrim("-42", "_-");
// 	printf("the string is: %s\n", b);
// 	free(b);
// 	char * c = ft_strtrim("+42", "_+");
// 	printf("the string is: %s\n", c);
// 	free(c);
// 	char * d = ft_strtrim("abc", "");
// 	printf("the string is: %s\n", d);
// 	free(d);
// 	char * e = ft_strtrim("", "");
// 	printf("the string is: %s\n", e);
// 	free(e);
// 	char * f = ft_strtrim("   xxxtripouille", " x");
// 	printf("the string is: %s\n", f);
// 	free(f);
// 	char * g = ft_strtrim("tripouille   xxx", " x");
// 	printf("the string is: %s\n", g);
// 	free(g);
// }