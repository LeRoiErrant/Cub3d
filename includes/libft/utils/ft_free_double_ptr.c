/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:28:01 by 0xNino            #+#    #+#             */
/*   Updated: 2022/04/04 11:40:29 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_double_ptr(void ***ptr)
{
	void	**tmp;

	if (*ptr)
	{
		tmp = *ptr;
		while (*tmp)
		{
			ft_free_ptr(tmp);
			tmp++;
		}
		free(*ptr);
		*ptr = NULL;
	}
}
