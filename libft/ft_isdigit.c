/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:45 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:27:39 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The isdigit() function tests for a decimal digit character. 

RETURN
The isdigit() and isnumber() functions return zero if the character tests
false and return non-zero if the character tests true.

PARAMETERS
c: input integer (0,1,2,...,9)

EXTERNAL FUNCTIONS
-
*/
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
// 	#include <ctype.h>
// 	#include <stdio.h>
// int main()
// {
// 	printf("%d\n", isdigit(58));
// 	printf("%d\n", ft_isdigit(58));
// }