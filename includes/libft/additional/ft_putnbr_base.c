/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:58:26 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strlen(base) == 0 || ft_strlen(base) == 1)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	i = 0;
	while (base[i])
	{
		while (base[j] && i != j)
		{
			if (base[j++] == base[i])
				return (0);
		}
		j = 0;
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int			i;
	int long	res;

	if (!(ft_check_base(base)))
		return ;
	i = ft_strlen(base);
	res = (unsigned int) nbr;
	if (res >= i)
	{
		ft_putnbr_base(res / i, base);
		ft_putnbr_base(res % i, base);
	}
	else
		ft_putchar(base[res]);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		if (ft_check_base(argv[2]))
		{
			ft_putnbr_base(atoi(argv[1]), argv[2]);
			printf("\n%X\n", atoi(argv[1]));
		}
	}
	else
		printf("argc error\n");
	return (0);
}
*/