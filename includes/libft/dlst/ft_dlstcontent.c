/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstcontent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:37:56 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 22:38:32 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_dlstcontent(t_dlist *dlst, size_t i)
{
	t_node	*node;

	if (!dlst || i > dlst->size)
		return (NULL);
	node = dlst->first;
	while (i--)
		node = node->next;
	return (node->content);
}
