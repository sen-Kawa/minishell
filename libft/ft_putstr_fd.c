/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:08:11 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:02 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
Outputs the string ’s’ to the given file
descriptor.

RETURN
none

PARAMETERS
s: The string to output.
fd: The file descriptor on which to write.

EXTERNAL FUNCTIONS
write
*/
void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (s && *s)
	{
		while (s[index] != '\0')
		{
			write(fd, &s[index], 1);
			index++;
		}	
	}
}
