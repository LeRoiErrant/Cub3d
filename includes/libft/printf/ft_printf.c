/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:08:38 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 16:21:10 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_specifier(char c, va_list args, int count)
{
	if (c == 'c')
		count += ft_putchar_len(va_arg(args, int));
	if (c == 's')
		count += ft_putstr_len(va_arg(args, char *));
	if (c == 'p')
		count += ft_puthex_len(va_arg(args, unsigned long), 'p');
	if (c == 'd' || c == 'i')
		count += ft_putnbr_len(va_arg(args, int), 'd');
	if (c == 'u')
		count += ft_putnbr_len(va_arg(args, unsigned int), 'u');
	if (c == 'x')
		count += ft_puthex_len(va_arg(args, unsigned int), 'x');
	if (c == 'X')
		count += ft_puthex_len(va_arg(args, unsigned int), 'X');
	if (c == '%')
		count += ft_putchar_len('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count = ft_specifier(format[i], args, count);
		}
		else
			count += ft_putchar_len(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
//	char	*str;
//	int		nbr;
//
//	str = NULL;
//	nbr = 0;
//	strlcpy(str, "Salut", 10);
	ft_printf("Hello world\n");
	ft_printf("Print a char : %c\n", 'A');
//	ft_printf("Print a string : %s\n", str);
//	ft_printf("Print a pointer : %p\n", );
//	ft_printf("Print an int %d\n", nbr);
}
*/
