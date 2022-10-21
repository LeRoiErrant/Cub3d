#include "../includes/cub3d.h"

void	gun(t_cub3d *cub)
{	
	int		frame;
	t_ipos	i;

	frame = cub->gun_frame;
	i.x = SCR_H - cub->tex[cub->gun_frame]->h;
	i.y = SCR_W / 2 - (cub->tex[cub->gun_frame]->w / 2);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->tex[frame]->img, i.y, i.x);
}
