/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:58:27 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:27:31 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The isalpha() function tests for any character for which
isupper(3) or islower(3) is true.  The value of the
argument must be representable as an unsigned char or the
value of EOF.

RETURN
The isalpha() function returns zero if the character tests false and
returns non-zero if the character tests true.

PARAMETERS
c: int valua of the charracter in ASCII connotation

EXTERNAL FUNCTIONS
malloc
*/
int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}
// 	#include <ctype.h>
// 	#include <stdio.h>
// int main()
// {
// 	printf("%d\n", isalpha(122));
// 	printf("%d\n", ft_isalpha(122));
// }