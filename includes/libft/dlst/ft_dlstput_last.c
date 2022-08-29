/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstput_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:52:49 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 22:53:01 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_dlist	*ft_dlstput_last(t_dlist *dlst, t_node *node)
{
	if (!node)
		return (dlst);
	if (!dlst)
		dlst = ft_dlstnew();
	if (!dlst)
		return (dlst);
	node->prev = dlst->last;
	node->next = NULL;
	if (dlst->last)
	{
		dlst->last->next = node;
		dlst->last = node;
	}
	else
	{
		dlst->first = node;
		dlst->last = node;
	}
	dlst->size++;
	return (dlst);
}
