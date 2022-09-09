/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:37:48 by ksura             #+#    #+#             */
/*   Updated: 2022/05/05 09:13:50 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.

RETURN
none

PARAMETERS
s: The string on which to iterate.
f: The function to apply to each character.

EXTERNAL FUNCTIONS
none
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	index;

	index = 0;
	if (s && f)
	{
		while (s[index] != '\0')
		{
			f(index, (s + index));
			index++;
		}
	}
}
