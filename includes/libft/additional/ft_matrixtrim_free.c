/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixtrim_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:39:49 by 0xNino            #+#    #+#             */
/*   Updated: 2022/10/12 11:02:32 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	**ft_matrixtrim_free(char **matrix, char *set)
{
	int		i;
	char	**tmp;

	if (!matrix)
		return (NULL);
	i = -1;
	printf("Matrix trim: %zu\n", ft_matrixlen(matrix));
	printf("Matrix trim: %zu\n", ft_matrixlen(matrix));
	tmp = ft_calloc(ft_matrixlen(matrix), sizeof(char *));
	if (!tmp)
		return (NULL);
	while (matrix && matrix[++i])
	{
		tmp[i] = ft_strtrim(matrix[i], set);
		printf("%i|%s|\n", i, tmp[i]);
		free(matrix[i]);
	}
	free(matrix);
	ft_printf("tmp address: %p\n", tmp);
	return (tmp);
}
