/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:52 by 0xNino            #+#    #+#             */
/*   Updated: 2022/05/15 18:20:55 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_matrixprint(char **matrix, int len, int fd)
{
	int	i;

	i = -1;
	if (len <= 0)
		len = ft_matrixlen(matrix);
	while (++i < len)
		ft_putendl_fd(matrix[i], fd);
	return ;
}
