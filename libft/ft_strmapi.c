/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:46:40 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:37 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’.

RETURN
The string created from the successive applications
of ’f’.
Returns NULL if the allocation fails.

PARAMETERS
s: The string on which to iterate.
f: The function to apply to each character.

EXTERNAL FUNCTIONS
malloc
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{	
	unsigned int	index;
	char			*res;

	if (!f)
		return (NULL);
	if (!s)
		return (NULL);
	index = 0;
	res = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[index] != '\0')
	{
		res[index] = f(index, s[index]);
		index++;
	}
	res[ft_strlen(s)] = '\0';
	return (res);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_strmapi("12345", addOne));
// }