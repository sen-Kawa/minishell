/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:29:16 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:28:45 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The memset() function writes len bytes of value c 
(converted to an unsigned char) to the string b.

RETURN
The memset() function returns its first argument.

PARAMETERS

EXTERNAL FUNCTIONS

*/
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_char;

	b_char = (unsigned char *)b;
	while (len-- > 0)
	{
		b_char[len] = c;
	}
	return (b);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     char str[50] = "What is memset really doing?.";
//     printf("\nBefore memset(): %s\n", str);	
//     // Fill 8 characters starting from str[13] with '.'
//     memset(str, '.', 2*sizeof(char));
//     printf("After memset():  %s", str);
//     char ftr[50] = "What is memset really doing?.";
//     printf("\nBefore ft_memset(): %s\n", ftr);	
// 	ft_memset(ftr, '.', 2*sizeof(char));
// 	printf("After memset():  %s", ftr);
//     return 0;
// }