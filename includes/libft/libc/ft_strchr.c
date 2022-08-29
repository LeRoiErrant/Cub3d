/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:12:27 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
/*
DESCRIPTION
The strchr() function locates the first occurrence of c (converted to a char)
in the string pointed to by s. The terminating null character is considered to
be part of the string; therefore if c is `\0', the functions locate the
terminating `\0'. The strrchr() function is identical to strchr(), except it
locates the last occurrence of c.

RETURN VALUES
The functions strchr() and strrchr() return a pointer to the located character,
or NULL if the character does not appear in the string.
*/
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}
