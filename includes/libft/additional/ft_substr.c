/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:29:21 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub = ft_calloc(1, sizeof(char));
		if (!sub)
			return (NULL);
		return (sub);
	}
	if (len > ft_strlen(s))
	{
		sub = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
		if (!sub)
			return (NULL);
	}
	else
	{
		sub = (char *)ft_calloc(len + 1, sizeof(char));
		if (!sub)
			return (NULL);
	}
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
