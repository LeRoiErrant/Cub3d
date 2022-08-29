/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_variadic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:49:00 by 0xNino            #+#    #+#             */
/*   Updated: 2022/05/16 15:49:00 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_variadic(unsigned int arg_count, ...)
{
	va_list			args;
	unsigned int	i;
	void			**ptr;

	va_start(args, arg_count);
	i = 0;
	while (i < arg_count)
	{
		ptr = va_arg(args, void **);
		ft_free_ptr(ptr);
		i++;
	}
	va_end(args);
	return ;
}
