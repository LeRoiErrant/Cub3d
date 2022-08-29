/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:51:09 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 22:51:13 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_node	*ft_dlstpush_first(t_dlist *dlst)
{
	t_node	*dst;

	if (!dlst || !dlst->first)
		return (NULL);
	dst = dlst->first;
	if (dst && dlst->first == dlst->last)
	{
		dlst->first = NULL;
		dlst->last = NULL;
	}
	else
	{
		dlst->first = dlst->first->next;
		dlst->first->prev = NULL;
		dst->next = NULL;
	}
	if (dlst->size)
		dlst->size--;
	return (dst);
}
