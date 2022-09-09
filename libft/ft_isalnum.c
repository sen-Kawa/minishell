/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:08:43 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:27:27 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The isalnum() function tests for any character for which isalpha(3) or
isdigit(3) is true.  The value of the argument must be representable as
an unsigned char or the value of EOF.

RETURN
The isalnum() function returns zero if the character tests false and
returns non-zero if the character tests true.

PARAMETERS
c: input integer if a character in ASCII

EXTERNAL FUNCTIONS
-
*/
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	else
		return (0);
}

// 	#include <ctype.h>
// 	#include <stdio.h>
// int main()
// {
// 	printf("%d\n", isalnum(58));
// 	printf("%d\n", ft_isalnum(58));
// }	