/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:53:06 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:28:49 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Outputs the character ’c’ to the given file
descriptor.

RETURN
none

PARAMETERS
c: The character to output.
fd: The file descriptor on which to write.

EXTERNAL FUNCTIONS
write
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
