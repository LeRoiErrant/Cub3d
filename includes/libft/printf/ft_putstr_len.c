/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:47:59 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 16:21:10 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_len(char *s)
{
	int		i;
	char	*empty;

	i = 0;
	empty = "(null)";
	if (!s)
	{
		while (*empty)
			write(1, empty++, 1);
		return (6);
	}
	while (*s)
	{
		write (1, s++, 1);
		i++;
	}
	return (i);
}
