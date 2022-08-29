/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:17:19 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 16:27:12 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_uintlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
