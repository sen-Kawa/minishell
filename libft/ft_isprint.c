/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:05:15 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:27:42 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The isprint() function tests for any printing character, including space
(` ').  The value of the argument must be representable as an unsigned
char or the value of EOF.

RETURN
The isprint() function returns zero if the character tests false and
returns non-zero if the character tests true.

PARAMETERS
c: input integer if a character in ASCII

EXTERNAL FUNCTIONS
-
*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
// 	#include <ctype.h>
// 	#include <stdio.h>
// int main()
// {
// 	printf("%d\n", isprint(40));
// 	printf("%d\n", ft_isprint(40));
// }