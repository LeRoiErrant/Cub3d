/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:14:38 by 0xNino            #+#    #+#             */
/*   Updated: 2022/04/12 13:14:38 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr_set(const char *str, const char *set)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!str || !set)
		return (NULL);
	while (set[i] && !tmp)
		tmp = ft_strchr(str, set[i++]);
	return (tmp);
}
