/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:57:40 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_atoi(const char *str)
{
	long	nbr;
	int		minus;

	nbr = 0;
	minus = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			minus = 1;
	while (ft_isdigit(*str))
	{
		if ((nbr > (FT_LONG_MAX - *str + '0') / 10) && minus)
			return (0);
		if ((nbr > (FT_LONG_MAX - *str + '0') / 10) && !minus)
			return (-1);
		nbr = 10 * nbr + (*str - '0');
		str++;
	}
	if (minus)
		return ((int)-nbr);
	return ((int)nbr);
}
