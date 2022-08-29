/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_first.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:33:27 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 22:34:59 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_dlist	*ft_dlststadd_first(t_dlist *dlst, void *content)
{
	t_node	*node;

	if (!dlst)
		dlst = ft_dlstnew();
	node = malloc(sizeof(t_node));
	if (!node)
		return (dlst);
	node->prev = NULL;
	node->next = dlst->first;
	node->content = content;
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
	if (node)
		dlst->size++;
	return (dlst);
}
