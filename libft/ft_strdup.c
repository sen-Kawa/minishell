/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:54:27 by ksura             #+#    #+#             */
/*   Updated: 2022/05/13 13:29:13 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The strdup() function allocates sufficient memory for a copy
of the string s1, does the copy, and returns a pointer to it.
The pointer may subsequently be used as an argument
to the function free(3).

If insufficient memory is available, NULL is returned
and errno is set to ENOMEM.

The strndup() function copies at most n characters from
the string s1 always NUL terminating the copied string.

RETURN
Pointer to the copied str.

PARAMETERS
s1: string to be copied

EXTERNAL FUNCTIONS
malloc
*/
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = malloc(len);
	if (ptr == NULL)
		return (0);
	ft_strlcpy(ptr, s1, len);
	return (ptr);
}
// int main()
// {
//     char original[20] = "T$Ester Te$st";
//     char *duplicate;
//     int o_len,d_len;

//     duplicate = ft_strdup(original);
//     o_len = ft_strlen(original);
//     d_len = ft_strlen(duplicate);

//     printf("Original String: '%s' (%d)\n",
//             original,o_len);
//     printf("Duplicate string: '%s' (%d)\n",
//             duplicate,d_len);
//     duplicate = strdup(original);
//     o_len = ft_strlen(original);
//     d_len = ft_strlen(duplicate);

//     printf("Original String: '%s' (%d)\n",
//             original,o_len);
//     printf("Duplicate string: '%s' (%d)\n",
//             duplicate,d_len);
//     return(0);
// }