/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 11:00:08 by ksura             #+#    #+#             */
/*   Updated: 2022/10/24 19:56:58 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
/*
DESCRIPTION
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.

RETURN
The array of new strings resulting from the split.
NULL if the allocation fails.

PARAMETERS
s: The string to be split.
c: The delimiter character.

EXTERNAL FUNCTIONS
malloc, free
*/
char			**ft_split(char const *s, char c);
static size_t	word_count(char const *s, char c);
static void		make_word(char const *s, char c, char **result, size_t wa);

char	**ft_split_ssp(char const *s, char c)
{
	char	**arr;
	size_t	wc;

	if (!s)
		return (NULL);
	if (!*s)
	{
		arr = (char **)malloc(sizeof(char *) * 1);
		if (!arr)
			return (NULL);
		arr[0] = 0;
		return (arr);
	}
	wc = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	make_word(s, c, arr, wc);
	return (arr);
}

static size_t	word_count(char const	*s, char c)
{
	size_t		indexw;

	indexw = 0;
	while (*s)
	{
		if (*s != c && *s != '\0')
		{
			while (*s != c && *s != '\0')
				s++;
		indexw++;
		}
		if (*s == c && *s != '\0')
		{
			while (*s == c && *s != '\0')
				s++;
		indexw++;
		}
	}
	return (indexw);
}

static void	make_word(char const	*s, char c, char **result, size_t wa)
{	
	size_t	i;
	size_t	i2;
	size_t	wordsize;

	i = 0;
	i2 = 0;
	wordsize = 0;
	while (i2 < wa && *s)
	{
		if (s[i + wordsize] == c && s[i + wordsize] != '\0')
		{
			while (s[i + wordsize] == c && s[i + wordsize] != '\0')
				wordsize++;
			result[i2] = ft_substr(s, i, wordsize);
			i2++;
			i = i + wordsize;
			wordsize = 0;
		}	
		else if (s[i + wordsize] != c && s[i + wordsize] != '\0')
		{
			while (s[i + wordsize] != c && s[i + wordsize] != '\0')
				wordsize++;
			result[i2] = ft_substr(s, i, wordsize);
			i2++;
			i = i + wordsize;
			wordsize = 0;
		}	
	}
	result[i2] = 0;
}
/*
int	word(int i2, char **result, char const *s, char c)
{

}	*/
