/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:57:39 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:24 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
strlcat() appends string src to the end of dst.  It will append at most
dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate,
unless dstsize is 0 or the original dst string was longer
than dstsize (in practice this should not happen as it means
that either dstsize is incorrect or that dst is not a proper string).

RETURN
initial length of dst plus the length of src

PARAMETER
dst: pointer to destination
src: pointer t source
destsize: max alltogether size of the resulting string
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	pos1;
	size_t	d_len;
	size_t	s_len;

	d_len = (size_t)ft_strlen(dst);
	s_len = (size_t)ft_strlen(src);
	if (dstsize <= d_len)
		return (s_len + dstsize);
	pos1 = 0;
	while (src[pos1] != '\0' && (dstsize - d_len) > 1)
	{
		dst[d_len + pos1] = src[pos1];
		pos1++;
		dstsize--;
	}
	dst[d_len + pos1] = '\0';
	return (d_len + s_len);
}
// #include <stdio.h>

// void test(int size)
// {
//     char string[] = "AAAAAAAAA";
//     char buffer[]= "B";
//     int len;

//     len = ft_strlcat(buffer,string,size);

//     printf("Appended '%s' to '%s', length %d\n",
//             string,
//             buffer,
//             len
//           );
// }

// int main()
// {
//     test(19);
//     test(10);
//     test(1);
//     test(0);

//     return(0);
// }