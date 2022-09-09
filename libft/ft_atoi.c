/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:13:42 by ksura             #+#    #+#             */
/*   Updated: 2022/06/08 18:33:29 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The atoi() function converts the initial portion of 
the string pointed to by str to
int representation.

RETURN
integer number of initial string

PARAMETER
str: pointer to string which to convert
*/
int	ft_atoi(const char *str)
{
	long int	n;
	int			m;

	n = 0;
	m = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		n = n * 10 + *str - '0';
		str++;
	}
	return (n * m);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main()
// {
//     long int val;
//     char strn1[] = "2147483648";

//     val = atoi(strn1);
//     printf("String value = _%s_\n", strn1);
//     printf("atoi_Integer value = %ld\n", val);
//     printf("ft_atoi Integer value = %d\n", ft_atoi(strn1));
//     char strn2[] = "-2147483649";
//     val = atol(strn2);
//     printf("String value = %s\n", strn2);
//     printf("atol_Integer value = %ld\n", val);
// 	printf("ft_atoi_Integer value = %d\n", ft_atoi(strn2));

//     return (0);
// }