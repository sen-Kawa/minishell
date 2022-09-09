/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:45:09 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:28 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
strlcpy() copies up to dstsize - 1 characters from the string src
to dst, NUL-terminating the result if dstsize is not 0.

RETURN
total length of
the string they tried to create.

PARAMETERS
dst: pointer to destination
src: pointer to source
dstsize: size of the destination

EXTERNAL FUNCTIONS

*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	pos;
	size_t	srcsize;

	pos = 0;
	srcsize = 0;
	while (*(src + pos) != '\0')
	{
		srcsize++;
		pos++;
	}
	if (dstsize == 0)
		return (srcsize);
	pos = 0;
	while (pos < (dstsize -1) && *src != '\0')
	{
		*(dst + pos) = *src;
		pos++;
		src++;
	}
	*(dst + pos) = '\0';
	return (srcsize);
}

// #include <stdio.h>
// #include <string.h>
// void test(int size)
// {
//     char string[] = "Whats up, Lamaaaaaaaa";
//     char buffer[22] = "empty";
//     int len;

//     len = ft_strlcpy(buffer,string,size);

//     printf("ft_Copied '%s' into '%s', length %d\n",
//             string,
//             buffer,
//             len
//           );
// 	len = strlcpy(buffer,string,size);

//     printf("Copied '%s' into '%s', length %d\n",
//             string,
//             buffer,
//             len
//           );
// }

// int main()
// {
//     test(19);
//     test(10);
//     test(6);
//     test(0);

//     return(0);
// }