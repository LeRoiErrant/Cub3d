/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:13:32 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/18 21:21:56 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	partition(int *arr, int start, int end)
{
	int	pivot;
	int	i;
	int	j;

	if (start >= end)
		return (-1);
	pivot = start;
	i = start;
	j = end;
	while (i < j)
	{
		while (arr[i] <= arr[pivot] && i < end)
			i++;
		while (arr[j] > arr[pivot])
			j--;
		if (i < j)
			ft_swap_int(&arr[i], &arr[j]);
	}
	ft_swap_int(&arr[pivot], &arr[j]);
	return (j);
}

void	ft_quicksort(int *arr, int start, int end)
{
	int	p;

	p = 0;
	if (start < end)
	{
		p = partition(arr, start, end);
		ft_quicksort(arr, start, p - 1);
		ft_quicksort(arr, p + 1, end);
	}
}
/*
int	main(int argc, char **argv)
{
	int	i;
	int	*i_arr;

	i_arr = ft_argv_to_i_arr(argc, argv);
	i = 0;
	printf("Array before sorting:\t");
	while (i < argc - 1)
	{
		printf("%d ", i_arr[i]);
		i++;
	}
	printf("\n");
	ft_quicksort (i_arr, 0, argc - 2);
	printf("Array after sorting:\t");
	i = 0;
	while (i < argc - 1)
	{
		printf("%d ", i_arr[i]);
		i++;
	}
	printf("\n");
}
*/