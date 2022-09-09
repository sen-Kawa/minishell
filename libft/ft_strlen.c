/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:47:44 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:33 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The strlen() function computes the length of the string s.  The strnlen()
function attempts to compute the length of s, but never scans beyond the
first maxlen bytes of s.

RETURN
The strlen() function returns the number of characters that precede the
terminating NUL character.  The strnlen() function returns either the
same result as strlen() or maxlen, whichever is smaller.

PARAMETERS
str: pointer to the string to be measured

EXTERNAL FUNCTIONS
-
*/
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		i++;
	}
	return (i);
}
