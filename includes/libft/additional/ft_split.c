/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:01:30 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_substrcount(char const *s, char c)
{
	size_t	count;
	int		in_substr;

	count = 0;
	in_substr = 0;
	while (*s)
	{
		if (in_substr == 1 && *s == c)
			in_substr = 0;
		if (in_substr == 0 && *s != c)
		{
			in_substr = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	ft_substrlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		strcount;
	int		index;

	if (!s)
		return (NULL);
	strcount = ft_substrcount(s, c);
	arr = (char **) malloc(sizeof(*arr) * (ft_substrcount(s, c) + 1));
	if (!arr)
		return (NULL);
	index = 0;
	while (strcount--)
	{
		while (*s && *s == c)
			s++;
		arr[index] = ft_substr(s, 0, ft_substrlen(s, c));
		if (!arr[index])
			return (NULL);
		s = s + ft_substrlen(s, c);
		index++;
	}
	arr[index] = NULL;
	return (arr);
}
