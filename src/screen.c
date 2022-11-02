/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:49:59 by vheran            #+#    #+#             */
/*   Updated: 2022/11/02 10:49:59 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_img	init_screen(t_cub3d *cub)
{
	t_img	scr;

	scr.img = mlx_new_image(cub->mlx, SCR_W, SCR_H);
	scr.addr = mlx_get_data_addr(scr.img, &scr.bpp, &scr.ll, &scr.endian);
	return (scr);
}

static t_img	init_minimap(t_cub3d *cub)
{
	t_img	map;

	map.img = mlx_new_image(cub->mlx, 130, 130);
	map.addr = mlx_get_data_addr(map.img, &map.bpp, &map.ll, &map.endian);
	return (map);
}

static t_img	init_gun(t_cub3d *cub)
{
	t_img	gun;
	int		width;
	int		height;

	width = cub->tex[cub->gun_frame]->w;
	height = cub->tex[cub->gun_frame]->h;
	gun.img = mlx_new_image(cub->mlx, width, height);
	gun.addr = mlx_get_data_addr(gun.img, &gun.bpp, &gun.ll, &gun.endian);
	return (gun);
}

void	init_images(t_cub3d *cub)
{
	cub->screen = init_screen(cub);
	cub->minimap = init_minimap(cub);
	cub->gun = init_gun(cub);
}
