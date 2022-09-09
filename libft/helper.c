/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:41:27 by ksura             #+#    #+#             */
/*   Updated: 2022/07/19 16:27:59 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(va_list	list);
int	print_char(va_list	list);
int	print_num(va_list	list);
int	print_unum(va_list	list);
int	write_char(char c);

int	write_char(char c)
{
	return (write(1, &c, 1));
}

int	print_str(va_list list)
{
	int		i;
	char	*str;

	str = va_arg(list, char *);
	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
	{
		write_char(str[i]);
		i++;
	}
	return (i);
}

int	print_char(va_list list)
{
	write_char(va_arg(list, int));
	return (1);
}

int	print_num(va_list list)
{
	int		a;
	int		i;
	char	*str;

	i = 0;
	a = va_arg(list, int);
	str = ft_itoa(a);
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		write_char(str[i]);
		i++;
	}
	free (str);
	return (i);
}

int	print_unum(va_list list)
{
	unsigned int	a;
	int				i;
	char			*str;

	i = 0;
	a = va_arg(list, unsigned int);
	str = ft_uitoa(a);
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		write_char(str[i]);
		i++;
	}
	free (str);
	return (i);
}
