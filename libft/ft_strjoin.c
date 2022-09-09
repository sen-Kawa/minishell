/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:00:39 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:20 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.

RETURN
The new string.
NULL if the allocation fails.

PARAMETERS
s1: The prefix string.
s2: The suffix string.

EXTERNAL FUNCTIONS
malloc
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*dst;

	len = (size_t)ft_strlen(s1) + (size_t)ft_strlen(s2) + 1;
	if (s1 == NULL && s1 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	dst = (char *)malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ((size_t)ft_strlen(s1) +1));
	ft_strlcat(dst + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (dst);
}
// #include <stdio.h>
// int main()
// {
// 	printf("the string is: %s\n", ft_strjoin("_HEyHEy_", "42"));
// 	printf("the string is: %s\n", ft_strjoin("", "42"));
// 	printf("the string is: %s\n", ft_strjoin("42", ""));
// 	printf("the string is: %s\n", ft_strjoin("", ""));
// }