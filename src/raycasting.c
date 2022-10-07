#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void ver_line(t_img *img, int x, int length, int color)
{
	int i;
	int	start;

	start = (SCREEN_H / 2) - (length / 2) - 1;
	i = start;
	if (length <= 0)
		return;
	while (++i - start != length)
		my_mlx_pixel_put(img, x, i, color);
}

/*double	get_deltadist(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	else
		return (fabs(1 / ray_dir));
}*/

void	first_step(t_cub3d *cub)
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

void	run_dda(t_cub3d *cub)
{
	while (cub->ray.hit == 0)
	{
		//? jump to next map square, either in x-direction, or in y-direction
		if (cub->ray.sidedist.x < cub->ray.sidedist.y)
		{
			cub->ray.sidedist.x += cub->ray.deltadist.x;
			cub->ray.map.x += cub->ray.step.x;
			if (cub->ray.step.x < 0)
				cub->ray.side = 0;
			else
				cub->ray.side = 2;
		}
		else
		{
			cub->ray.sidedist.y += cub->ray.deltadist.y;
			cub->ray.map.y += cub->ray.step.y;
			if (cub->ray.step.y < 0)
				cub->ray.side = 1;
			else
				cub->ray.side = 3;
		}
		//? Check if ray has hit a wall
		if (cub->map[cub->ray.map.x][cub->ray.map.y] == '1')
			cub->ray.hit = 1;
	}
}

double	calculate_perp_dist(t_cub3d *cub)
{
	if (cub->ray.side % 2 == SIDE_X)
		return (cub->ray.sidedist.x - cub->ray.deltadist.x);
	else
		return (cub->ray.sidedist.y - cub->ray.deltadist.y);
}

int	raycasting(t_cub3d *cub)
{
	int	x;

	t_img	img;

	img.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);

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
		cub->ray.deltadist.x = fabs(1 / cub->ray.raydir.x);
		cub->ray.deltadist.y = fabs(1 / cub->ray.raydir.y);
	
		/*cub->ray.deltadist.x = get_deltadist(cub->ray.raydir.x);
		cub->ray.deltadist.y = get_deltadist(cub->ray.raydir.y);*/
		
		cub->ray.hit = 0;

		//? calculate step and initial sideDist
		first_step(cub);

		//? perform DDA
		run_dda(cub);
		
		//? Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		cub->ray.line_info.perpwalldist = calculate_perp_dist(cub);

		//? Calculate height of line to draw on screen
		cub->ray.line_info.height = (int) (SCREEN_H / cub->ray.line_info.perpwalldist);

		//? calculate lowest and highest pixel to fill in current stripe
		cub->ray.line_info.drawstart = (-cub->ray.line_info.height / 2) + (SCREEN_H / 2);
		if (cub->ray.line_info.drawstart < 0)
			cub->ray.line_info.drawstart = 0;
		cub->ray.line_info.drawend = (cub->ray.line_info.height / 2) + (SCREEN_H / 2);
		if (cub->ray.line_info.drawend >= SCREEN_H)
			cub->ray.line_info.drawend = SCREEN_H - 1;
		/*
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
		*/
		int color;


		if (cub->ray.side == SIDE_X)
			color = 0x00FF0000;
		else if (cub->ray.side == SIDE_Y)
			color = 0x00AB0000;
		else if (cub->ray.side == 2)
			color = 0x0000FF00;
		else
			color = 0x0000AB00;
		ver_line(&img, x, cub->ray.line_info.drawend - cub->ray.line_info.drawstart, color);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, img.img, 0, 0);
	mlx_destroy_image(cub->mlx, img.img);
	free(cub->tex.array);
	return (0);
}
