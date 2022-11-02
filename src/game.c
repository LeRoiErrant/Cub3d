/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:44:10 by 0xNino            #+#    #+#             */
/*   Updated: 2022/11/02 10:44:11 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	loop(t_cub3d *cub)
{
	init_images(cub);
	raycasting(cub);
	minimap(cub);
	update_cam(cub);
	update_pos(cub);
	animation(cub);
	gun(cub);
	mlx_destroy_image(cub->mlx, cub->screen.img);
	mlx_destroy_image(cub->mlx, cub->minimap.img);
	mlx_destroy_image(cub->mlx, cub->gun.img);
	return (0);
}

void	game(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCR_W, SCR_H, "cub3d");
	init_bground(cub);
	init_tex(cub);
	mlx_mouse_move(cub->win, (int)(SCR_W / 2), (int)(SCR_H / 2));
	mlx_mouse_hide(cub->win);
	mlx_hook(cub->win, ON_DESTROY, 0, exit_cub, cub);
	mlx_hook(cub->win, ON_KEYDOWN, 0, key_down, cub);
	mlx_hook(cub->win, ON_KEYUP, 0, key_release, cub);
	mlx_hook(cub->win, ON_MOUSEMOVE, 0, mouse_move, cub);
	mlx_hook(cub->win, ON_MOUSEDOWN, 0, mouse_down, cub);
	mlx_loop_hook(cub->mlx, &loop, cub);
	mlx_loop(cub->mlx);
}
