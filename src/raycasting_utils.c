#include "../includes/cub3d.h"

double	calculate_perp_dist(t_cub3d *cub)
{
	if (cub->ray.side % 2 == SIDE_X)
		return (cub->ray.sidedist.x - cub->ray.deltadist.x);
	else
		return (cub->ray.sidedist.y - cub->ray.deltadist.y);
}

void	does_it_hit(t_cub3d *cub)
{
	t_ipos	i;

	i.x = (int) cub->ray.map.x;
	i.y = (int) cub->ray.map.y;
	if (cub->map[i.x][i.y] == '1')
		check_open_door(cub, i.x, i.y, cub->ray.side);
	else if (cub->map[i.x][i.y] == 'D')
		check_door_hit(cub);
}

void	draw_column(t_cub3d *cub, int x)
{
	int		i;
	int		color;

	i = -1;
	while (++i < SCREEN_H)
	{
		if (i < cub->ray.line_info.drawstart)
			color = distance_shade(cub->config.ceiling.rgb, (double) i / (SCREEN_H / 6.5));
		else if (i <= cub->ray.line_info.drawend)
			color = distance_shade(get_tex_color(cub), cub->ray.line_info.perpwalldist);
		else
			color = distance_shade(cub->config.floor.rgb, ((double) SCREEN_H - i) / (SCREEN_H / 6.5));
		if (color)
			my_mlx_pixel_put(&cub->screen, x, i, color);
	}
}
