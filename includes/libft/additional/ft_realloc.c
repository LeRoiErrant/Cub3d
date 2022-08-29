/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:26:23 by 0xNino            #+#    #+#             */
/*   Updated: 2022/04/20 15:26:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	old_size;

	if (!ptr)
		return (malloc(new_size));
	old_size = ft_strlen((char *) ptr);
	if (new_size <= old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	ft_memcpy(new_ptr, ptr, old_size);
	ft_free_ptr((void **)ptr);
	return (new_ptr);
}
