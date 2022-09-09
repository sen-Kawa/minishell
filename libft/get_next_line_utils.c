/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:03:05 by ksura             #+#    #+#             */
/*   Updated: 2022/07/05 12:30:21 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*calloc_gnl(int count)
{
	char	*ptr;
	int		index;

	if (count == 0)
		count = 1;
	index = 0;
	ptr = malloc(count * sizeof(char));
	if (!ptr)
		return (NULL);
	while (index > 0)
		ptr[index--] = '\0';
	return (ptr);
}

char	*strchr_gnl(const char *line)
{
	if (!line)
		return (0);
	while (*line != '\0')
	{
		if (*line == '\n')
			return ((char *)line);
		line++;
	}
	return (0);
}

int	strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i) != '\0')
		i++;
	return (i);
}

char	*strjoin_gnl(char *s1, char *s2)
{
	size_t	index1;
	size_t	index2;
	char	*str;

	if (!s1)
	{
		s1 = (char *)calloc_gnl(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = calloc_gnl((strlen_gnl(s1) + strlen_gnl(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	index1 = -1;
	index2 = 0;
	if (s1)
		while (s1[++index1] != '\0')
			str[index1] = s1[index1];
	while (s2[index2] != '\0')
		str[index1++] = s2[index2++];
	str[strlen_gnl(s1) + strlen_gnl(s2)] = '\0';
	free(s1);
	return (str);
}
