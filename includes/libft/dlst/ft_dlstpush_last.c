/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush_last.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:51:36 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 22:51:53 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_node	*ft_dlstpush_last(t_dlist *dlst)
{
	t_node	*dst;

	if (!dlst || !dlst->first)
		return (NULL);
	dst = dlst->last;
	if (dst && dlst->first == dlst->last)
	{
		dlst->first = NULL;
		dlst->last = NULL;
	}
	else
	{
		dlst->last = dlst->last->prev;
		dlst->last->next = NULL;
		dst->prev = NULL;
	}
	if (dlst->size)
		dlst->size--;
	return (dst);
}
