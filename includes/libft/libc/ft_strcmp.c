/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 20:20:14 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/17 20:22:55 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
/*
DESCRIPTION
The strcmp() and strncmp() functions lexicographically compare the
null-terminated strings s1 and s2. The strncmp() function compares not morethan
n characters.  Because strncmp() is designed for comparing strings rather than
binary data, characters that appear after a `\0' character are not compared.

RETURN VALUES
The strcmp() and strncmp() functions return an integer greater than, equal to,
or less than 0, according as the string s1 is greater than, equal to, or less
than the string s2.  The comparison is done using unsigned characters,
so that `\200' is greater than `\0'.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
