/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:12:30 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/28 18:15:34 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_print_i_arr(int *i_arr, int size, char *name)
{
	int	i;

	i = 0;
	ft_printf("arr size = %i\t%s : ", size, name);
	while (i < size)
	{
		ft_printf("[%i]", i_arr[i]);
		if (i < size - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
