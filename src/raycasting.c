#include "../includes/cub3d.h"

double	get_deltadist(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	else
		return (fabs(1 / ray_dir));
}

int	raycasting(t_cub3d *cub)
{
	int	x;

	cub->tex.array = malloc(sizeof(int) * (SCREEN_W + 1));
	if (!cub->tex.array)
		return (E_MALLOC);
	x = -1;
	while (++x <= SCREEN_W)
	{
		//? calculate ray position and direction
		cub->ray.camera.x = 2 * x / (double) SCREEN_W - 1;
		cub->ray.raydir.x = cub->dir.x + cub->plane.x * cub->ray.camera.x;
		cub->ray.raydir.y = cub->dir.y + cub->plane.y * cub->ray.camera.x;

		//? which box of the map we're in
		cub->ray.map.x = (int) cub->pos.x; 
		cub->ray.map.y = (int) cub->pos.y; 

		//? length of ray from one x or y-side to next x or y-side
		cub->ray.deltadist.x = get_deltadist(cub->ray.raydir.x);
		cub->ray.deltadist.y = get_deltadist(cub->ray.raydir.y);
		cub->ray.hit = 0;
		//? calculate step and initial sideDist
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
			cub->ray.sidedist.y = (cub->pos.y - cub->ray.map.y) * cub->ray.deltadist.x;
		}
		else
		{
			cub->ray.step.y = 1;
			cub->ray.sidedist.y = (cub->ray.map.y + 1.0 - cub->pos.y) * cub->ray.deltadist.y;
		}
		//? perform DDA
		while (cub->ray.hit == 0)
		{
			//? jump to next map square, either in x-direction, or in y-direction
			if (cub->ray.sidedist.x < cub->ray.sidedist.y)
			{
				cub->ray.sidedist.x += cub->ray.deltadist.x;
				cub->ray.map.x += cub->ray.step.x;
				cub->ray.side = 0;
			}
			else
			{
				cub->ray.sidedist.y += cub->ray.deltadist.x;
				cub->ray.map.y += cub->ray.step.y;
				cub->ray.side = 1;
			}
			//? Check if ray has hit a wall
			if (cub->map[cub->ray.map.x][cub->ray.map.y] == '1')
				cub->ray.hit = 1;
		}
		//? Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (cub->ray.side == 0)
			cub->ray.line_info.perpwalldist = cub->ray.sidedist.x - cub->ray.deltadist.x;
		else
			cub->ray.line_info.perpwalldist = cub->ray.sidedist.y - cub->ray.deltadist.y;
		//? Calculate height of line to draw on screen
		cub->ray.line_info.height = (int) (SCREEN_H / cub->ray.line_info.perpwalldist);
		//? calculate lowest and highest pixel to fill in current stripe
		cub->ray.line_info.drawstart = -cub->ray.line_info.height / 2 + SCREEN_H / 2;
		if (cub->ray.line_info.drawstart < 0)
			cub->ray.line_info.drawstart = 0;
		cub->ray.line_info.drawend = cub->ray.line_info.height / 2 + SCREEN_H / 2;
		if (cub->ray.line_info.drawend >= SCREEN_H)
			cub->ray.line_info.drawend = SCREEN_H - 1;
		//? calculate value of wallX
		if (cub->ray.side == 0)
			cub->tex.wall.x = cub->pos.y + cub->ray.line_info.perpwalldist * cub->ray.raydir.y;
		else
			cub->tex.wall.x = cub->pos.x + cub->ray.line_info.perpwalldist * cub->ray.raydir.x;
		cub->tex.wall.x -= floor(cub->tex.wall.x);
		//? x coordinate on the texture
		cub->tex.x = (int) (cub->tex.wall.x * (double) TEXTURE_W);
		if (cub->ray.side == 0 && cub->ray.raydir.x > 0)
			cub->tex.x = TEXTURE_W - cub->tex.x - 1;
		if (cub->ray.side == 1 && cub->ray.raydir.y < 0)
			cub->tex.x = TEXTURE_W - cub->tex.x - 1;
		//? How much to increase the texture coordinate per screen pixel
		cub->tex.step = 1.0 * TEXTURE_H / cub->ray.line_info.height;
		//? Starting texture coordinate
		cub->tex.pos = (cub->ray.line_info.drawstart - SCREEN_H / 2 + cub->ray.line_info.height / 2) * cub->tex.step;
		t_img	texture;
		(void) texture;
		if (cub->ray.side)
		{
			if (cub->ray.raydir.y < 0)
				texture = *cub->textures.north;
			else
				texture = *cub->textures.south;
		}
		else
		{
			if (cub->ray.raydir.x < 0)
				texture = *cub->textures.west;
			else
				texture = *cub->textures.east;
		}
		//TODO load texture line
		//TODO draw image
	}
	free(cub->tex.array);
	return (0);
}
