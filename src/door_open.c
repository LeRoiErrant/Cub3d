#include "../includes/cub3d.h"

static t_ipos	door_range(t_cub3d *cub)
{
	t_ipos	pos;
	int		loop;
	double	mult;

	loop = 1;
	mult = 0.1;
	pos.x = (int)(cub->pos.x + (mult * cub->ray.step.x));
	pos.y = (int)(cub->pos.y + (mult * cub->ray.step.y));
	while (loop && mult <= 1.5)
	{
		if (cub->map[pos.x][pos.y] == 'D' || cub->map[pos.x][pos.y] == 'O')
			loop = 0;
		else
		{
			mult += 0.1;
			pos.x = (int)(cub->pos.x + (mult * cub->dir.x));
			pos.y = (int)(cub->pos.y + (mult * cub->dir.y));
		}
	}
	return (pos);
}

void	open_door(t_cub3d *cub)
{
	t_ipos	pos;
	int		pos_x;
	int		pos_y;

	pos = door_range(cub);
	pos_x = (int) cub->pos.x;
	pos_y = (int) cub->pos.y;
	if (cub->map[pos.x][pos.y] == 'D')
		cub->map[pos.x][pos.y] = 'O';
	else if (cub->map[pos.x][pos.y] == 'O' && cub->map[pos_x][pos_y] != 'O')
		cub->map[pos.x][pos.y] = 'D';
}
