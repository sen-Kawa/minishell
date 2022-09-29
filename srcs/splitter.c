/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:14:26 by ksura             #+#    #+#             */
/*   Updated: 2022/09/29 09:49:21 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char			**ft_split(char const *s, char c);
static size_t	word_count(char const *s, char c);
static void		make_word(char const *s, char c, char **result, size_t wa);

char	**ft_split_sp(char const *s, char c)
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
	while (*s == c)
		s++;
	while (*s)
	{
		indexw++;
		while (*s != c && *s != '\0')
			s++;
		while (*s == c && *s != '\0')
			s++;
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
		while (s[i + wordsize] == c && s[i + wordsize] != '\0')
		{
			wordsize++;
		}
		i = i + wordsize;
		wordsize = 0;
		while (s[i + wordsize] != c && s[i + wordsize] != '\0')
			wordsize++;
		result[i2] = ft_substr(s, i, wordsize);
		i2++;
		i = i + wordsize;
	}
	result[i2] = 0;
}
