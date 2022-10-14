#include "../includes/cub3d.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	get_color(t_img *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->ll + x * (img->bpp / 8));
	return (*(int *)color);
}


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

void d_square(t_img *img, int x, int y, int length, int color)
{
	t_ipos 	i;
	t_ipos	start;

	start.x = x;
	start.y = y;
	i.x = start.x;
	if (length <= 0)
		return;
	while (++i.x - start.x != length)
	{
		i.y = start.y;
		while (++i.y - start.y != length)
			my_mlx_pixel_put(img, i.x, i.y, color);
	}
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

int	get_tex_color(t_cub3d *cub)
{
	cub->o_tex.y = (int) cub->o_tex.pos & (TEXTURE_H - 1);
	cub->o_tex.pos += cub->o_tex.step;
	cub->o_tex.color = get_color(cub->tex[cub->ray.side], cub->o_tex.x, cub->o_tex.y);
	return (cub->o_tex.color);
}

void	draw_column(t_cub3d *cub, int x)
{
	int	i;
	int	color;

	i = -1;
	while (++i < SCREEN_H)
	{
		if (i < cub->ray.line_info.drawstart)
			color = distance_shade(cub->config.ceiling.rgb, (double) i / (SCREEN_H / 12));
		else if (i <= cub->ray.line_info.drawend)
			color = distance_shade(get_tex_color(cub), cub->ray.line_info.perpwalldist);
		else
			color = distance_shade(cub->config.floor.rgb,  ((double) SCREEN_H - i) / (SCREEN_H / 12));
		my_mlx_pixel_put(&cub->screen, x, i, color);
	}
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
	
		
		//? calculate value of wallX
		if (cub->ray.side % 2 == SIDE_X)
			cub->o_tex.wall.x = cub->pos.y + cub->ray.line_info.perpwalldist * cub->ray.raydir.y;
		else
			cub->o_tex.wall.x = cub->pos.x + cub->ray.line_info.perpwalldist * cub->ray.raydir.x;
		cub->o_tex.wall.x -= floor(cub->o_tex.wall.x);
		
		//? x coordinate on the texture
		cub->o_tex.x = (int) (cub->o_tex.wall.x * (double) TEXTURE_W);

		if (cub->ray.side % 2 == SIDE_X && cub->ray.raydir.x > 0)
			cub->o_tex.x = TEXTURE_W - cub->o_tex.x - 1;
		if (cub->ray.side % 2 == SIDE_Y && cub->ray.raydir.y < 0)
			cub->o_tex.x = TEXTURE_W - cub->o_tex.x - 1;
		
		//? How much to increase the texture coordinate per screen pixel
		cub->o_tex.step = 1.0 * TEXTURE_H / cub->ray.line_info.height;
		
		//? Starting texture coordinate
		cub->o_tex.pos = (cub->ray.line_info.drawstart - SCREEN_H / 2 + cub->ray.line_info.height / 2) * cub->o_tex.step;
		/*int	y;

		y = cub->ray.line_info.drawstart - 1;
		while (++y <= cub->ray.line_info.drawend)
		{
			cub->o_tex.y = (int) cub->o_tex.pos & (TEXTURE_H - 1);
			cub->o_tex.pos += cub->o_tex.step;
			cub->o_tex.color = get_color(cub->tex[cub->ray.side], cub->o_tex.x, cub->o_tex.y);
			my_mlx_pixel_put(&cub->screen, x, y, cub->o_tex.color);
		}*/
		draw_column(cub, x);
		//TODO load texture line
		//TODO draw image
		/*
		int color;
		int	i;
		double	dist;

		dist = cub->ray.line_info.perpwalldist;
		color = cub->config.ceiling.rgb;
		i = -1;
		while (++i < SCREEN_H / 2)
			my_mlx_pixel_put(&cub->screen, x, i, color);
		color = cub->config.floor.rgb;
		while (i < SCREEN_H)
			my_mlx_pixel_put(&cub->screen, x, i++, color);
		if (cub->ray.side == TEX_NO)
			color = distance_shade (0x00783114, dist);
		else if (cub->ray.side == TEX_WE)
			color = distance_shade(0x00963d19, dist);
		else if (cub->ray.side == TEX_SO)
			color = distance_shade(0x00602710, dist);
		else if (cub->ray.side == TEX_EA)
			color = distance_shade(0x006e351e, dist);
		ver_line(&cub->screen, x, cub->ray.line_info.drawend - cub->ray.line_info.drawstart, color);
	*/
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	free(cub->o_tex.array);
	return (0);
}
