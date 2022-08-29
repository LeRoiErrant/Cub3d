/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:39:15 by 0xNino            #+#    #+#             */
/*   Updated: 2022/04/12 10:09:03 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_dlstclear(t_dlist **dlst)
{
	t_node	*current;
	t_node	*next;

	if (!*dlst)
		return ;
	current = (*dlst)->first;
	if (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}	
	while (current && current != (*dlst)->first)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(*dlst);
	*dlst = NULL;
}
