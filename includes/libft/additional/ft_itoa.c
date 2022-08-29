/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:56:25 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	size_t	nbr;

	len = ft_intlen(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		nbr = (size_t) n * -1;
		str[0] = '-';
	}
	else
		nbr = n;
	while (nbr > 0)
	{
		str[--len] = 48 + (nbr % 10);
		nbr /= 10;
	}
	return (str);
}
