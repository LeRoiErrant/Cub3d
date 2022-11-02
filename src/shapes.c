/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:50:02 by vheran            #+#    #+#             */
/*   Updated: 2022/11/02 10:50:03 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ver_line(t_img *img, int x, int length, int color)
{
	int	i;
	int	start;

	start = (SCR_H / 2) - (length / 2) - 1;
	i = start;
	if (length <= 0)
		return ;
	while (++i - start != length)
		my_mlx_pixel_put(img, x, i, color);
}

void	d_cell(t_img *img, int x, int y, int color)
{
	t_ipos	i;
	int		length;

	length = 10;
	i.x = x - 1;
	if (length <= 0)
		return ;
	while (++i.x - x != length)
	{
		i.y = y - 1;
		while (++i.y - y != length)
			my_mlx_pixel_put(img, i.x, i.y, color);
	}
}

int	in_circle(float x, float y)
{
	float	distance;

	distance = sqrtf(powf(x - 4.5, 2.) + powf(y - 4.5, 2.));
	if (distance <= 3.45)
		return (1);
	return (0);
}
