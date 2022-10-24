/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:20:51 by 0xNino            #+#    #+#             */
/*   Updated: 2022/10/12 11:31:50 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
/*
DESCRIPTION
The ft_matrixlen() function computes the length of the 2D matrix.

/!\ Only use with initialized memory (ft_calloc).

RETURN VALUES
The ft_matrixlen() function returns the number of characters that precede the
terminating NUL character.
*/
size_t	ft_matrixlen(char **matrix)
{
	size_t	len;

	len = 0;
	while (matrix && matrix[len])
		len++;
	return (len);
}
