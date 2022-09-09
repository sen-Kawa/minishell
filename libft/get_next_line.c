/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 09:39:58 by ksura             #+#    #+#             */
/*   Updated: 2022/07/05 12:29:54 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*get_next_line(int fd)
{
	char		*line_out;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_saverest_gnl(fd, rest);
	if (!rest)
		return (NULL);
	line_out = line_output_gnl(rest);
	rest = save_rest(rest);
	return (line_out);
}

char	*read_saverest_gnl(int fd, char	*rest)
{
	char	*buffer;
	int		byte_count;

	buffer = calloc_gnl((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	byte_count = 1;
	while (!strchr_gnl(rest) && byte_count != 0)
	{
		byte_count = read(fd, buffer, BUFFER_SIZE);
		if (byte_count == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[byte_count] = '\0';
		rest = strjoin_gnl(rest, buffer);
	}
	free(buffer);
	return (rest);
}

char	*line_output_gnl(char	*rest)
{
	int		index;
	char	*rest_str;

	index = 0;
	if (!rest[index])
		return (NULL);
	while (rest[index] && rest[index] != '\n')
		index++;
	rest_str = (char *)calloc_gnl(sizeof(char) * (index + 2));
	if (!rest_str)
		return (NULL);
	index = 0;
	while (rest[index] && rest[index] != '\n')
	{
		rest_str[index] = rest[index];
		index++;
	}
	if (rest[index] == '\n')
	{
		rest_str[index] = rest[index];
		index++;
	}
	rest_str[index] = '\0';
	return (rest_str);
}

char	*save_rest(char	*rest)
{
	int		i1;
	int		i2;
	char	*ret_str;

	i1 = 0;
	while (rest[i1] && rest[i1] != '\n')
		i1++;
	if (!rest[i1])
	{
		free (rest);
		return (NULL);
	}
	ret_str = (char *)calloc_gnl(sizeof(char) * (strlen_gnl(rest) - i1 + 2));
	if (!ret_str)
		return (NULL);
	i1++;
	i2 = 0;
	while (rest[i1])
		ret_str[i2++] = rest[i1++];
	ret_str[i2] = '\0';
	free(rest);
	return (ret_str);
}
