/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:23:33 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:27:46 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
DESCRIPTION
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.

RETURN
The string representing the integer.
NULL if the allocation fails.

PARAMETERS
n: the integer to convert.

EXTERNAL FUNCTIONS
malloc
*/
char			*ft_itoa(int n);
static size_t	numtodig(int n);
static void		numtostr(int n, char *str, size_t dig, size_t neg);

char	*ft_itoa(int n)
{
	int		dig;
	size_t	neg;
	char	*num;

	dig = numtodig(n);
	num = (char *)malloc(sizeof(char) * (dig +1));
	if (num == NULL)
		return (NULL);
	if (n >= 0)
	{
		neg = 0;
		numtostr(n, num, dig, neg);
	}
	else
	{
		neg = 1;
		numtostr(n, num, dig, neg);
		num[0] = '-';
	}
	num[dig] = '\0';
	return (num);
}

static size_t	numtodig(int a)
{
	size_t	i;

	i = 1;
	if (a < 0)
		i++;
	while (a > 9 || a < -9)
	{
		a = a / 10;
		i++;
	}
	return (i);
}

static void	numtostr(int n, char *str, size_t dig, size_t neg)
{
	while (dig > neg)
	{
		if (n < 0)
		{
			str[--dig] = -(n % 10) + '0';
			n = n / 10;
		}
		else
		{
			str[--dig] = (n % 10) + '0';
			n = n / 10;
		}
	}
}
// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_itoa(-123));
// }