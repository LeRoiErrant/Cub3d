#include "../includes/cub3d.h"

static t_ipos	door_range(t_cub3d *cub)
{
	t_ipos	coord;
	int		loop;
	double	mult;

	loop = 1;
	mult = 0.1;
	coord.x = (int)(cub->pos.x + (mult * cub->ray.step.x));
	coord.y = (int)(cub->pos.y + (mult * cub->ray.step.y));
	while (loop && mult <= 1.5)
	{
		if (cub->map[coord.x][coord.y] == 'D' || cub->map[coord.x][coord.y] == 'O')
			loop = 0;
		else
		{
			mult += 0.1;
			coord.x = (int)(cub->pos.x + (mult * cub->dir.x));
			coord.y = (int)(cub->pos.y + (mult * cub->dir.y));
		}
	}
	return (coord);
}

void	open_door(t_cub3d *cub)
{
	t_ipos	coord;
	int		pos_x;
	int		pos_y;

	coord = door_range(cub);
	pos_x = (int) cub->pos.x;
	pos_y = (int) cub->pos.y;
	if (cub->map[coord.x][coord.y] == 'D')
		cub->map[coord.x][coord.y] = 'O';
	else if (cub->map[coord.x][coord.y] == 'O' && cub->map[pos_x][pos_y] != 'O')
		cub->map[coord.x][coord.y] = 'D';
}
