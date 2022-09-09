/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:44:32 by ksura             #+#    #+#             */
/*   Updated: 2022/07/19 16:28:20 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
DESCRIPTION
The printf utility formats and prints its arguments, after the first,
under control of the format.  The format is a character string which
contains three types of objects: plain characters, which are simply
copied to standard output, character escape sequences which are
converted and copied to the standard output, and format specifications,
each of which causes printing of the next successive argument.
*/
int		ft_printf(const char	*format, ...);
int		ft_hexlow(va_list	list, char ca);
int		write_char(char c);
int		ft_percent(void);
void	rules(int *i, const char *format, int *count_print, va_list argptr);

int	ft_printf(const char *format, ...)
{
	va_list	argptr;
	int		i;
	int		count_print;

	i = 0;
	count_print = 0;
	va_start(argptr, format);
	while (format[i])
	{
		if (format[i] == '%')
			rules(&i, format, &count_print, argptr);
		else
		{
			write(1, &format[i], 1);
			count_print++;
		}
		i++;
	}
	va_end (argptr);
	return (count_print);
}

void	rules(int *i, const char *format, int *count_print, va_list argptr)
{
	*i = *i + 1;
	if (format[*i] == 'c')
		*count_print += print_char(argptr);
	else if (format[*i] == 's')
		*count_print += print_str(argptr);
	else if (format[*i] == 'p')
		*count_print += print_point(argptr);
	else if (format[*i] == 'd' || format[*i] == 'i')
		*count_print += print_num(argptr);
	else if (format[*i] == 'u')
		*count_print += print_unum(argptr);
	else if (format[*i] == 'x' || format[*i] == 'X')
		*count_print += ft_hexlow(argptr, format[*i]);
	else if (format[*i] == '%')
		*count_print += ft_percent();
	else
		*i = *i - 1;
}

int	ft_percent(void)
{
	write(1, "%%", 1);
	return (1);
}
