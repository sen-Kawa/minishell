/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:25:32 by ksura             #+#    #+#             */
/*   Updated: 2022/05/05 09:04:52 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
The tolower() function converts an upper-case letter to the corresponding
lower-case letter.  The argument must be representable as an unsigned
char or the value of EOF.

Although the tolower() function uses the current locale, the tolower_l()
function may be passed a locale directly. See xlocale(3) for more infor-
mation.

RETURN
If the argument is an upper-case letter, the tolower() function returns
the corresponding lower-case letter if there is one; otherwise, the argu-
ment is returned unchanged.

PARAMETER
c: character to be changed
*/
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 32;
	}
	return (c);
}
