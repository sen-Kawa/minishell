/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:32:30 by ksura             #+#    #+#             */
/*   Updated: 2022/05/05 09:04:47 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
The strchr() function locates the first occurrence of c (converted to a
char) in the string pointed to by s.  The terminating null character is
considered to be part of the string; therefore if c is `\0', the func-
tions locate the terminating `\0'.

The strrchr() function is identical to strchr(), except it locates the
last occurrence of c.

RETURN
The functions strchr() and strrchr() return a pointer to the located
character, or NULL if the character does not appear in the string.

PARAMETER
c: character to search for in s
s: pointer to str in which to look for c
*/
char	*ft_strchr(const char *s, int c)
{
	char	c_char;

	c_char = (char)c;
	while (*s != c_char && *s != '\0')
	{
		s++;
	}
	if (*s == c_char)
		return ((char *)s);
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     const char str[50] = "What\0is ft_strchr really doing?.";
// 	int a = 'i';
// 	printf("%x\n", (unsigned int)ft_strchr(str, a));
// 	printf("%x\n", (unsigned int) strchr(str, a));
// }