/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:48:03 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 16:21:10 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoh(char *hex, int len, unsigned long n, char specifier)
{
	unsigned long	reminder;

	reminder = 0;
	len--;
	while (n)
	{
		reminder = n % 16;
		hex[len--] = ft_htoc(reminder, specifier);
		n /= 16;
	}
	return (hex);
}
/*
int	main(int argc, char **argv)
{
	char	*hex;

	hex = ft_calloc(atoi(argv[1]) + 1, sizeof(char));
	if (argc == 4)
	{
		printf("%s\n", ft_itoh(hex, atoi(argv[1]), atoi(argv[2]), argv[3][0]));
	}
}
*/