/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstput_first.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:52:17 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 22:52:28 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_dlist	*ft_dlstput_first(t_dlist *dlst, t_node *node)
{
	if (!node)
		return (dlst);
	if (!dlst)
		dlst = ft_dlstnew();
	if (!dlst)
		return (NULL);
	node->prev = NULL;
	node->next = dlst->first;
	if (dlst->first)
	{
		dlst->first->prev = node;
		dlst->first = node;
	}
	else
	{
		dlst->first = node;
		dlst->last = node;
	}
	dlst->size++;
	return (dlst);
}
