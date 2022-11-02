/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:49:31 by vheran            #+#    #+#             */
/*   Updated: 2022/11/02 10:49:32 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_camera(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_RIGHT)
		cub->engine.rot.right = 1;
	if (keycode == KEY_LEFT)
		cub->engine.rot.left = 1;
}

void	update_cam(t_cub3d *cub)
{
	double	olddirx;
	double	oldplanex;
	double	rsp;

	rsp = cub->config.rotspeed;
	if (cub->engine.rot.right)
	{
		olddirx = cub->dir.x;
		cub->dir.x = cub->dir.x * cos(-rsp) - cub->dir.y * sin(-rsp);
		cub->dir.y = olddirx * sin(-rsp) + cub->dir.y * cos(-rsp);
		oldplanex = cub->plane.x;
		cub->plane.x = cub->plane.x * cos(-rsp) - cub->plane.y * sin(-rsp);
		cub->plane.y = oldplanex * sin(-rsp) + cub->plane.y * cos(-rsp);
	}
	if (cub->engine.rot.left)
	{
		olddirx = cub->dir.x;
		cub->dir.x = cub->dir.x * cos(rsp) - cub->dir.y * sin(rsp);
		cub->dir.y = olddirx * sin(rsp) + cub->dir.y * cos(rsp);
		oldplanex = cub->plane.x;
		cub->plane.x = cub->plane.x * cos(rsp) - cub->plane.y * sin(rsp);
		cub->plane.y = oldplanex * sin(rsp) + cub->plane.y * cos(rsp);
	}
}

void	move_validation(t_cub3d *cub, t_dpos move)
{
	t_ipos	coord;

	coord.x = (int)(cub->pos.x + move.x);
	coord.y = (int)(cub->pos.y + move.y);
	if (cub->map[coord.x][coord.y] == '1' || cub->map[coord.x][coord.y] == 'D'
			|| cub->map[coord.x][coord.y] == '.')
		return ;
	cub->pos.x += move.x;
	cub->pos.y += move.y;
	cub->pc.x = cub->pos.x * 10;
	cub->pc.y = cub->pos.y * 10;
}

void	update_pos(t_cub3d *cub)
{
	if (cub->engine.move.up)
	{
		cub->engine.delta.x = cub->dir.x * cub->config.movespeed;
		cub->engine.delta.y = cub->dir.y * cub->config.movespeed;
	}
	if (cub->engine.move.down)
	{
		cub->engine.delta.x = -1 * cub->dir.x * cub->config.movespeed;
		cub->engine.delta.y = -1 * cub->dir.y * cub->config.movespeed;
	}
	if (cub->engine.move.left)
	{
		cub->engine.delta.x = -1 * cub->dir.y * cub->config.movespeed;
		cub->engine.delta.y = cub->dir.x * cub->config.movespeed;
	}
	if (cub->engine.move.right)
	{
		cub->engine.delta.x = cub->dir.y * cub->config.movespeed;
		cub->engine.delta.y = -1 * cub->dir.x * cub->config.movespeed;
	}
	move_validation(cub, cub->engine.delta);
	cub->engine.delta.x = 0;
	cub->engine.delta.y = 0;
}

void	check_movement(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W)
		cub->engine.move.up = 1;
	if (keycode == KEY_S)
		cub->engine.move.down = 1;
	if (keycode == KEY_A)
		cub->engine.move.left = 1;
	if (keycode == KEY_D)
		cub->engine.move.right = 1;
}
