/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:39:51 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/28 15:46:15 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_dlstisordered(t_dlist *dlst, int (*f)(t_node *, t_node *))
{
	t_node	*current;

	if (!dlst || dlst->size == 0)
		return (0);
	if (dlst->size == 1)
		return (1);
	current = dlst->first;
	while (current->next)
	{
		if (f(current, current->next))
			return (0);
		current = current->next;
	}
	return (1);
}

void	ft_dlstprintint(t_dlist *dlst, char *name)
{
	t_node	*current;

	ft_printf("lst size = %i\t%s : ", (int) dlst->size, name);
	if (!dlst->size)
		ft_printf("\n");
	current = dlst->first;
	while (current)
	{
		ft_printf("[%i]", *(int *)current->content);
		current = current->next;
		if (current)
			ft_printf(" ");
		else
			ft_printf("\n");
	}
}

t_dlist	*ft_dlstcpy(t_dlist *dlst, void *(*f)(void *))
{
	t_dlist	*dlstdst;
	t_node	*node;

	if (!dlst || !f)
		return (NULL);
	dlstdst = ft_dlstnew();
	if (!dlstdst)
		return (NULL);
	if (!dlst->size)
		return (dlstdst);
	node = dlst->first;
	while (node)
	{
		ft_dlstadd_last(dlstdst, f(node->content));
		node = node->next;
	}
	return (dlstdst);
}
