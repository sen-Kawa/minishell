/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:10:28 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:27:35 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The isascii() function tests for an ASCII character, which is any charac-
ter between 0 and octal 0177 inclusive.

RETURN
The isascii() function returns zero if the character tests false and
returns non-zero if the character tests true.

PARAMETERS
c: input integer if a character in ASCII

EXTERNAL FUNCTIONS
-
*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
// 	#include <ctype.h>
// 	#include <stdio.h>
// int main()
// {
// 	printf("%d\n", isascii(0));
// 	printf("%d\n", ft_isascii(0));
// }