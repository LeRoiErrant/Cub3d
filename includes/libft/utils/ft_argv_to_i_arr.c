/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_to_i_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:07:43 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/18 21:09:49 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	*ft_argv_to_i_arr(int argc, char **argv)
{
	int	*i_arr;
	int	i;

	i_arr = malloc(sizeof(int) * (argc - 1));
	i = 1;
	while (i < argc)
	{
		i_arr[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (i_arr);
}
