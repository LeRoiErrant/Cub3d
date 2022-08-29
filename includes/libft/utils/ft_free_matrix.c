/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:48:15 by 0xNino            #+#    #+#             */
/*   Updated: 2022/05/04 15:22:40 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_matrix(char ***matrix)
{
	int	i;

	i = -1;
	while (matrix && matrix[0] && matrix[0][++i])
		free(matrix[0][i]);
	if (matrix)
	{
		free(matrix[0]);
		matrix[0] = NULL;
	}
}
