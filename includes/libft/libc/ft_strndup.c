/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:28:40 by vheran            #+#    #+#             */
/*   Updated: 2022/04/07 17:50:27 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(char *s, int n)
{
	char	*dup;
	int		l;

	if (!s)
		return (0);
	l = ft_strlen(s);
	if (n < l)
		l = n;
	dup = malloc((l + 1) * sizeof(*dup));
	if (!dup)
		return (0);
	ft_memmove(dup, s, l);
	dup[l] = '\0';
	return (dup);
}
