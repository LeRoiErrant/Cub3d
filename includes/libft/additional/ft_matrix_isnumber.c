/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_isnumber.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:39:57 by 0xNino            #+#    #+#             */
/*   Updated: 2022/10/03 21:39:57 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_matrix_isnumber(char **matrix)
{
	size_t	i;

	i = -1;
	while (++i < ft_matrixlen(matrix))
	{
		if (!ft_isnumber(matrix[i]))
			return (0);
	}
	return (1);
}
