#include "../includes/cub3d.h"

void	gun(t_cub3d *cub)
{	
	int		frame;
	t_ipos	i;

	frame = cub->gun_frame;
	i.x = SCREEN_H - cub->tex[cub->gun_frame]->h;
	i.y = SCREEN_W / 2 - (cub->tex[cub->gun_frame]->w / 2);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->tex[frame]->img, i.y, i.x);
}

int	update(t_cub3d *cub)
{
	init_screen_win(cub);
	raycasting(cub);
	minimap(cub);
	update_cam(cub);
	update_pos(cub);
	animation(cub);
	gun(cub);
	mlx_destroy_image(cub->mlx, cub->screen.img);
	mlx_destroy_image(cub->mlx, cub->minimap.img);
	mlx_destroy_image(cub->mlx, cub->gun.img);
	return (0);
}

static t_img	init_bground(t_cub3d *cub)
{
	t_img	bground;

	cub->config.floor.rgb = create_trgb(cub->config.floor);
	cub->config.ceiling.rgb = create_trgb(cub->config.ceiling);
	bground.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	bground.addr = mlx_get_data_addr(bground.img, &bground.bpp, &bground.ll, &bground.endian);
	cub->bground = bground;
	return (bground);
}	

void	loop(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H, "cub3d");
	init_bground(cub);
	mlx_mouse_move(cub->win, (int)(SCREEN_W / 2), (int)(SCREEN_H / 2));
	mlx_mouse_hide(cub->win);
	mlx_hook(cub->win, ON_DESTROY, 0, exit_cub, cub);
	mlx_hook(cub->win, ON_KEYDOWN, 0, key_down, cub);
	mlx_hook(cub->win, ON_KEYUP, 0, key_release, cub);
	mlx_hook(cub->win, ON_MOUSEMOVE, 0, mouse_move, cub);
	mlx_hook(cub->win, ON_MOUSEDOWN, 0, mouse_down, cub);
	init_tex(cub);
	cub->door_side = TEX_SIDE0;
	mlx_loop_hook(cub->mlx, &update, cub);
	mlx_loop(cub->mlx);
}
