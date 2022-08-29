/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:21:34 by 0xNino            #+#    #+#             */
/*   Updated: 2022/05/04 23:14:14 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	**ft_matrixdup(char **matrix)
{
	char	**dup;
	int		len;
	int		i;

	i = 0;
	len = ft_matrixlen(matrix);
	if (len <= 0)
		return (NULL);
	dup = (char **) ft_calloc(len + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	while (matrix[i])
	{
		dup[i] = ft_strdup(matrix[i]);
		if (!dup[i])
		{
			ft_free_matrix(&dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
