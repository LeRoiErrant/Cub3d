/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstunlink.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:45:47 by vheran            #+#    #+#             */
/*   Updated: 2022/05/18 14:20:56 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_dlstunlink(t_node *node, t_dlist *dlst)
{
	t_node	*prev;
	t_node	*next;

	if (node)
	{
		prev = node->prev;
		next = node->next;
		if (prev)
			prev->next = next;
		else
			dlst->first = next;
		if (next)
			next->prev = prev;
		else
			dlst->last = prev;
		dlst->size--;
		free(node->content);
		free(node);
	}
}
