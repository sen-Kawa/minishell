/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:24:25 by ksura             #+#    #+#             */
/*   Updated: 2022/07/20 09:16:06 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

/*
DESCRIPTION

RETURN
The string representing the integer.
NULL if the allocation fails.

PARAMETERS
n: the unsigned integer to convert to hexadecimal str.

EXTERNAL FUNCTIONS
malloc
*/
int			ft_hexlow(va_list list, char ca);
static int	putstr(int i, int j, char *c);
static char	*convstr(char ca);

int	ft_hexlow(va_list list, char ca)
{
	unsigned int		n;
	char				*c;
	int					i;
	int					j;

	c = calloc(12, sizeof(char));
	n = va_arg(list, int);
	i = 1;
	if (n == 0)
	{
		write(1, "0", 1);
		free(c);
		return (1);
	}
	while (n > 0)
	{
		c[i] = convstr(ca)[n % 16];
		n = n / 16;
		i++;
	}
	j = putstr(i, 0, c);
	free(c);
	return (j);
}

int	print_point(va_list list)
{
	uintptr_t	n;
	char		*c;
	int			i;
	int			j;

	c = calloc(20, sizeof(char));
	n = va_arg(list, uintptr_t);
	i = 1;
	write (1, "0x", 2);
	j = 2;
	if (n == 0)
	{
		write(1, "0", 1);
		free(c);
		return (3);
	}
	while (n > 0)
	{
		c[i] = "0123456789abcdef"[n % 16];
		n = n / 16;
		i++;
	}
	j = putstr(i, j, c);
	free(c);
	return (j);
}

static int	putstr(int i, int j, char *c)
{
	while (--i > 0)
	{
		write(1, &c[i], 1);
		j++;
	}
	return (j);
}

static char	*convstr(char ca)
{
	char	*str;

	if (ca == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	return (str);
}
