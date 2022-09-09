/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:51:00 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:28:58 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Outputs the integer ’n’ to the given file
descriptor.

RETURN
none

PARAMETERS
n: The integer to output.
fd: The file descriptor on which to write.

EXTERNAL FUNCTIONS
write
*/
void	ft_putnbr_fd(int n, int fd)
{	
	if (n == 0)
		ft_putchar_fd(n + '0', fd);
	else if (n >= 1 && n < 10)
		ft_putchar_fd(n + '0', fd);
	else if (n < 0 && n > -10)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd((n * -1) + '0', fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((n / 10) * -1, fd);
		ft_putchar_fd((n % 10) * -1 + '0', fd);
	}
}
