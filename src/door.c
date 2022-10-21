#include "../includes/cub3d.h"

void	check_door_hit_x(t_cub3d *cub)
{
	double	offset;
	double	wall;
	t_ipos	i;

	i.x = cub->ray.map.x;
	i.y = cub->ray.map.y;
	offset = 0.5 * cub->ray.step.x;
	offset += (1 - cub->ray.step.x) / 2;
	cub->ray.line_info.perpwalldist = cub->ray.map.x - cub->pos.x + offset;
	cub->ray.line_info.perpwalldist /= cub->ray.raydir.x;
	wall = cub->pos.y + cub->ray.line_info.perpwalldist * cub->ray.raydir.x;
	wall -= (int) wall;
	if (cub->ray.sidedist.x - (cub->ray.deltadist.x / 2) >= cub->ray.sidedist.y)
	{
		cub->ray.map.y += cub->ray.step.y;
		cub->ray.sidedist.y += cub->ray.deltadist.y;
		cub->ray.side = SIDE_Y;
		cub->ray.door.tex = cub->door_side;
		cub->ray.line_info.perpwalldist = 0;
	}
	else
		cub->ray.door.tex = TEX_CLS;
}

void	check_door_hit_y(t_cub3d *cub)
{
	double	offset;
	double	wall;

	offset = 0.5 * cub->ray.step.y;
	offset += (1 - cub->ray.step.y) / 2;
	cub->ray.line_info.perpwalldist = cub->ray.map.y - cub->pos.y + offset;
	cub->ray.line_info.perpwalldist /= cub->ray.raydir.y;
	wall = cub->pos.x + cub->ray.line_info.perpwalldist * cub->ray.raydir.y;
	wall -= (int) wall;
	if (cub->ray.sidedist.y - (cub->ray.deltadist.y / 2) >= cub->ray.sidedist.x)
	{
		cub->ray.map.x += cub->ray.step.x;
		cub->ray.sidedist.x += cub->ray.deltadist.x;
		cub->ray.side = SIDE_X;
		cub->ray.door.tex = cub->door_side;
		cub->ray.line_info.perpwalldist = 0;
	}
	else
		cub->ray.door.tex = TEX_CLS;
}

void	check_door_hit(t_cub3d *cub)
{
	cub->ray.hit = 1;
	if (cub->ray.side % 2 == SIDE_X)
		check_door_hit_x(cub);
	else
		check_door_hit_y(cub);
}

void	check_door(t_cub3d *cub, int x, int y, t_ipos d)
{
	if (x < 0 || SCR_H <= x || y < 0 || SCR_W <= y)
		return ;
	if (x - d.x < 0 || SCR_H <= x - d.x || y - d.y < 0 || SCR_W <= y - d.y)
		return ;
	if (cub->map[x][y] == 'O' && cub->map[x - d.x][y - d.y] == '1')
		cub->ray.door.tex = cub->door_side - 5;
	else
		cub->ray.door.tex = 0;
}

void	check_open_door(t_cub3d *cub, int x, int y, int side)
{
	t_ipos	d;

	cub->ray.hit = 1;
	d.x = 0;
	d.y = 0;
	if (side == TEX_NO || side == TEX_SO)
	{
		d.x = cub->ray.step.x;
		check_door(cub, x - cub->ray.step.x, y, d);
	}
	else if (side == TEX_WE || side == TEX_EA)
	{
		d.y = cub->ray.step.y;
		check_door(cub, x, y - cub->ray.step.y, d);
	}
}
