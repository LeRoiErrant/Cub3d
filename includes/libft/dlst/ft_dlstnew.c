/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:29:37 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 22:32:45 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_dlist	*ft_dlstnew(void)
{
	t_dlist	*dlst;

	dlst = malloc(sizeof(t_dlist));
	if (!dlst)
		return (dlst);
	dlst->size = 0;
	dlst->first = NULL;
	dlst->last = NULL;
	return (dlst);
}
