/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 09:21:18 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 14:29:22 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The memmove() function copies len bytes from string src to
string dst.  The two strings may overlap; the copy is
always done in a non-destructive manner.

RETURN
The memmove() function returns the original value of dst.

PARAMETERS
dst: destination pointer
src: source pointer
len: number of bytes to copy 

EXTERNAL FUNCTIONS

*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_char;
	const unsigned char	*src_char;

	dst_char = (unsigned char *)dst;
	src_char = (const unsigned char *)src;
	if ((dst == NULL) && (src == NULL))
		return (NULL);
	if (dst_char < src_char)
	{
		while (len > 0)
		{
			*dst_char = *src_char;
			dst_char++;
			src_char++;
			len--;
		}
	}
	else
	{
		while (len--)
			*(dst_char + len) = *(src_char + len);
	}
	return (dst);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char str[50] = "What is memmove really doing?.";
// 	char str2[50] = "It's replacing something!";
//     printf("\nBefore memmove(): %s\n", str);	
//     // Filling the old str with the new str
//     memmove(str, str2, 25*sizeof(char));
//     printf("After memmove():  %s", str);
//     char ftr[50] = "What is memmove really doing?.";
//     printf("\nBefore memmove(): %s\n", ftr);	
// 	ft_memmove(ftr + 31 , str2 + 2, 1 * sizeof(char));
// 	printf("After ft_memmove():  %s", ftr);

// 	char tr[] = {65, 66, 67, 68, 69, 0, 45};
// 	char tr2[] = { 0,  0,  0,  0,  0,  0, 0};
// 	printf("\nBefore memmove(): %s\n", str);	
//     // Filling the old str with the new str
//     memmove(tr2, tr, 7);
//     printf("After memmove():  %s", tr);
//     char ftr1[50] = "What is memmove really doing?.";
//     printf("\nBefore memmove(): %s\n", ftr1);	
// 	ft_memmove(tr2, tr, 7);
// 	printf("After ft_memmove():  %s", ftr1);
//     return 0;
// }