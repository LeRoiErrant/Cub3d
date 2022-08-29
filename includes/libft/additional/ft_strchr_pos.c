/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:13:55 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
/*
Find the first occurence of any character from the string set inside
the string s and returns its position.
*/
int	ft_strchr_pos(const char *s, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s || !set)
		return (-1);
	while (s[i])
	{
		j = 0;
		while (set[j])
			if (s[i] == set[j++])
				return (i);
		i++;
	}
	return (-1);
}
