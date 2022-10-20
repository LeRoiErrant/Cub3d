#include "../includes/cub3d.h"

static void	set_raydir_deltadist(t_cub3d *cub, int x)
{
	cub->ray.hit = 0;
	cub->ray.line_info.perpwalldist = 0;
	cub->ray.map.x = (int) cub->pos.x;
	cub->ray.map.y = (int) cub->pos.y;
	cub->ray.camera.x = 2 * x / (double) SCREEN_W - 1;
	cub->ray.raydir.x = cub->dir.x + cub->plane.x * cub->ray.camera.x;
	cub->ray.raydir.y = cub->dir.y + cub->plane.y * cub->ray.camera.x;
	cub->ray.deltadist.x = fabs(1 / cub->ray.raydir.x);
	cub->ray.deltadist.y = fabs(1 / cub->ray.raydir.y);
}

static void	set_step_sidedist(t_cub3d *cub)
{
	if (cub->ray.raydir.x < 0)
	{
		cub->ray.step.x = -1;
		cub->ray.sidedist.x = (cub->pos.x - cub->ray.map.x) * cub->ray.deltadist.x;
	}
	else
	{
		cub->ray.step.x = 1;
		cub->ray.sidedist.x = (cub->ray.map.x + 1.0 - cub->pos.x) * cub->ray.deltadist.x;
	}
	if (cub->ray.raydir.y < 0)
	{
		cub->ray.step.y = -1;
		cub->ray.sidedist.y = (cub->pos.y - cub->ray.map.y) * cub->ray.deltadist.y;
	}
	else
	{
		cub->ray.step.y = 1;
		cub->ray.sidedist.y = (cub->ray.map.y + 1.0 - cub->pos.y) * cub->ray.deltadist.y;
	}
}

static void	run_dda(t_cub3d *cub)
{
	while (cub->ray.hit == 0)
	{
		cub->ray.door.tex = 0;
		if (cub->ray.sidedist.x < cub->ray.sidedist.y)
		{
			cub->ray.sidedist.x += cub->ray.deltadist.x;
			cub->ray.map.x += cub->ray.step.x;
			if (cub->ray.step.x < 0)
				cub->ray.side = TEX_NO;
			else
				cub->ray.side = TEX_SO;
		}
		else
		{
			cub->ray.sidedist.y += cub->ray.deltadist.y;
			cub->ray.map.y += cub->ray.step.y;
			if (cub->ray.step.y < 0)
				cub->ray.side = TEX_WE;
			else
				cub->ray.side = TEX_EA;
		}
		does_it_hit(cub);
	}
}

static void	set_texture(t_cub3d *cub)
{
	if (!cub->ray.line_info.perpwalldist)
		cub->ray.line_info.perpwalldist = calculate_perp_dist(cub);
	cub->ray.line_info.height = (int)(SCREEN_H / cub->ray.line_info.perpwalldist);
	cub->ray.line_info.drawstart = (-cub->ray.line_info.height / 2) + (SCREEN_H / 2);
	if (cub->ray.line_info.drawstart < 0)
		cub->ray.line_info.drawstart = 0;
	cub->ray.line_info.drawend = (cub->ray.line_info.height / 2) + (SCREEN_H / 2);
	if (cub->ray.line_info.drawend >= SCREEN_H)
		cub->ray.line_info.drawend = SCREEN_H - 1;
	if (cub->ray.side % 2 == SIDE_X)
		cub->o_tex.wall.x = cub->pos.y + cub->ray.line_info.perpwalldist * cub->ray.raydir.y;
	else
		cub->o_tex.wall.x = cub->pos.x + cub->ray.line_info.perpwalldist * cub->ray.raydir.x;
	cub->o_tex.wall.x -= floor(cub->o_tex.wall.x);
	cub->o_tex.x = (int)(cub->o_tex.wall.x * (double) TEXTURE_W);
	if (cub->ray.side % 2 == SIDE_X && cub->ray.raydir.x > 0)
		cub->o_tex.x = TEXTURE_W - cub->o_tex.x - 1;
	if (cub->ray.side % 2 == SIDE_Y && cub->ray.raydir.y < 0)
		cub->o_tex.x = TEXTURE_W - cub->o_tex.x - 1;
	cub->o_tex.step = 1.0 * TEXTURE_H / cub->ray.line_info.height;
	cub->o_tex.pos = (cub->ray.line_info.drawstart - SCREEN_H / 2 + cub->ray.line_info.height / 2) * cub->o_tex.step;
}

int	raycasting(t_cub3d *cub)
{
	int	x;

	cub->o_tex.array = malloc(sizeof(int) * (SCREEN_W + 1));
	if (!cub->o_tex.array)
		return (E_MALLOC);
	x = -1;
	while (++x < SCREEN_W)
	{
		set_raydir_deltadist(cub, x);
		set_step_sidedist(cub);
		run_dda(cub);
		set_texture(cub);
		draw_column(cub, x);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	free(cub->o_tex.array);
	return (0);
}
