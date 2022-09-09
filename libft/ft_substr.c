/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 09:01:10 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:57 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.

RETURN
The substring.
NULL if the allocation fails.

PARAMETERS
s: The string from which to create the substring.
start: The start index of the substring in the
string ’s’.
len: The maximum length of the substring.

EXTERNAL FUNCTIONS
malloc
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	int		i;
	size_t	l;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= (unsigned int) ft_strlen(s))
		return (ft_strdup(""));
	l = ft_strlen(s + start);
	if (len > l)
		len = l;
	dst = (char *)malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	while (*(s + start) != '\0' && len > 0)
	{
		*(dst + i) = *(s + start);
		i++;
		start++;
		len--;
	}
	*(dst + i) = '\0';
	return (dst);
}
