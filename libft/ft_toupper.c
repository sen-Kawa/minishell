/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:17:53 by ksura             #+#    #+#             */
/*   Updated: 2022/05/05 09:04:55 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
The toupper() function converts a lower-case letter to the corresponding
upper-case letter.  The argument must be representable as an unsigned
char or the value of EOF.
Although the toupper() function uses the current locale, the toupper_l()
function may be passed a locale directly. See xlocale(3) for more infor-
mation.

RETURN
If the argument is a lower-case letter, the toupper() function returns
the corresponding upper-case letter if there is one; otherwise, the argu-
ment is returned unchanged.

PARAMETER
c: character to be changed
*/
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c - 32;
	}
	return (c);
}
