/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:45:55 by 0xNino            #+#    #+#             */
/*   Updated: 2022/11/02 10:45:56 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_config(t_cub3d *cub)
{
	cub->config.ceiling.red = -1;
	cub->config.ceiling.green = -1;
	cub->config.ceiling.blue = -1;
	cub->config.floor.red = -1;
	cub->config.floor.green = -1;
	cub->config.floor.blue = -1;
	cub->config.path[TEX_NO] = NULL;
	cub->config.path[TEX_WE] = NULL;
	cub->config.path[TEX_SO] = NULL;
	cub->config.path[TEX_EA] = NULL;
	cub->config.movespeed = 0.02;
	cub->config.rotspeed = 0.02;
	cub->config.map_w = 0;
	cub->config.map_h = 0;
}

static void	init_engine(t_cub3d *cub)
{
	cub->engine.move.up = 0;
	cub->engine.move.left = 0;
	cub->engine.move.down = 0;
	cub->engine.move.right = 0;
	cub->engine.rot.left = 0;
	cub->engine.rot.right = 0;
	cub->engine.delta.x = 0;
	cub->engine.delta.y = 0;
}

void	init_cub(t_cub3d *cub)
{
	cub->dir.x = 0.0;
	cub->dir.y = 0.0;
	cub->plane.x = 0;
	cub->plane.y = 0;
	cub->reset_buffer = 0;
	cub->map = NULL;
	cub->tmp = NULL;
	cub->errnum = SUCCESS;
	cub->color = 0;
	cub->gun_frame = TEX_GUN0;
	cub->door_side = TEX_SIDE0;
	cub->shoot = 0;
	cub->framecount = 0;
	cub->g_framecount = 0;
	cub->appear = 0;
	cub->mouse_enable = 1;
	init_config(cub);
	init_engine(cub);
}

t_img	init_bground(t_cub3d *cub)
{
	t_img	bgrd;

	cub->config.floor.rgb = create_trgb(cub->config.floor);
	cub->config.ceiling.rgb = create_trgb(cub->config.ceiling);
	bgrd.img = mlx_new_image(cub->mlx, SCR_W, SCR_H);
	bgrd.addr = mlx_get_data_addr(bgrd.img, &bgrd.bpp, &bgrd.ll, &bgrd.endian);
	cub->bground = bgrd;
	return (bgrd);
}

int	init_tex(t_cub3d *cub)
{
	int	i;
	int	check;

	i = -1;
	check = SUCCESS;
	while (++i < TEX_END)
	{
		cub->tex[i] = ft_calloc(1, sizeof(t_img));
		cub->tex[i]->img = mlx_xpm_file_to_image(cub->mlx, cub->config.path[i],
				&cub->tex[i]->w, &cub->tex[i]->h);
		cub->tex[i]->addr = mlx_get_data_addr(cub->tex[i]->img,
				&cub->tex[i]->bpp, &cub->tex[i]->ll, &cub->tex[i]->endian);
	}
	return (check);
}
