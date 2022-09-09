/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:24:25 by ksura             #+#    #+#             */
/*   Updated: 2022/07/19 16:27:41 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.

RETURN
The string representing the integer.
NULL if the allocation fails.

PARAMETERS
n: the unsigned integer to convert.

EXTERNAL FUNCTIONS
malloc
*/
char			*ft_uitoa(unsigned int n);
static size_t	numtodig(unsigned int n);
static void		numtostr(unsigned int n, char *str, size_t dig);

char	*ft_uitoa(unsigned int n)
{
	size_t	dig;
	char	*num;

	dig = numtodig(n);
	num = (char *)malloc(sizeof(char) * (dig +1));
	if (num == NULL)
		return (NULL);
	numtostr(n, num, dig);
	num[dig] = '\0';
	return (num);
}

static size_t	numtodig(unsigned int a)
{
	size_t	i;

	i = 1;
	if (a == 0)
		return (i);
	while (a > 9)
	{
		a = a / 10;
		i++;
	}
	return (i);
}

static void	numtostr(unsigned int n, char *str, size_t dig)
{
	while (dig > 0)
	{
		str[--dig] = (n % 10) + '0';
		n = n / 10;
	}
}
