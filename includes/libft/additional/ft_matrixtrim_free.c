/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixtrim_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:39:49 by 0xNino            #+#    #+#             */
/*   Updated: 2022/10/03 21:39:52 by 0xNino           ###   ########.fr       */
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
	tmp = ft_calloc(ft_matrixlen(matrix), sizeof(char *));
	if (!tmp)
		return (NULL);
	while (matrix && matrix[++i])
	{
		tmp[i] = ft_strtrim(matrix[i], set);
		free(matrix[i]);
	}
	free(matrix);
	return (tmp);
}
