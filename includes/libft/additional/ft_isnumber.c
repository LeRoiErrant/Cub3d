/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:55:37 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/13 18:00:02 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isnumber(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ' ' && str[i])
		return (-i);
	return (i);
}
