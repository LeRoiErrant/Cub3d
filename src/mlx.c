#include "../includes/cub3d.h"

int	exit_cub(t_cub3d *cub)
{
//	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_image(cub->mlx, cub->buf.img);
	mlx_destroy_image(cub->mlx, cub->textures.north->img);
	mlx_destroy_image(cub->mlx, cub->textures.east->img);
	mlx_destroy_image(cub->mlx, cub->textures.south->img);
	mlx_destroy_image(cub->mlx, cub->textures.west->img);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->textures.north);
	free(cub->textures.south);
	free(cub->textures.east);
	free(cub->textures.west);
	free_cub(cub);
	exit(cub->errnum);
}

void	rotate_camera(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_RIGHT)
		cub->engine.rot.right = 1;
    if (keycode == KEY_LEFT)
		cub->engine.rot.left = 1;
}

void	update_cam(t_cub3d *cub)
{
	if (cub->engine.rot.right)
    {
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(-cub->config.rotspeed) - cub->dir.y * sin(-cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(-cub->config.rotspeed) + cub->dir.y * cos(-cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(-cub->config.rotspeed) - cub->plane.y * sin(-cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(-cub->config.rotspeed) + cub->plane.y * cos(-cub->config.rotspeed);
    }
    //rotate to the left
    if (cub->engine.rot.left)
    {
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(cub->config.rotspeed) - cub->dir.y * sin(cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(cub->config.rotspeed) + cub->dir.y * cos(cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(cub->config.rotspeed) - cub->plane.y * sin(cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(cub->config.rotspeed) + cub->plane.y * cos(cub->config.rotspeed);
    }
}

void	move_validation(t_cub3d *cub, t_dpos move)
{
	t_ipos	coord;

	coord.x = (int) (cub->pos.x + move.x);
	coord.y = (int) (cub->pos.y + move.y);
	if (cub->map[coord.x][coord.y] == '1')
		return;
	cub->pos.x += move.x;
	cub->pos.y += move.y;
	cub->pc.x = cub->pos.x * 10;
	cub->pc.y = cub->pos.y * 10;
}

void	update_pos(t_cub3d *cub)
{
	if (cub->engine.move.up)
    {
		cub->engine.delta.x = cub->dir.x * cub->config.movespeed;
		cub->engine.delta.y = cub->dir.y * cub->config. movespeed;
    }
    if (cub->engine.move.down)
    {
      	cub->engine.delta.x = -1 * cub->dir.x * cub->config.movespeed;
		cub->engine.delta.y = -1 * cub->dir.y * cub->config.movespeed;
    }
	if (cub->engine.move.left)
    {
      	cub->engine.delta.x = -1 * cub->dir.y * cub->config.movespeed;
		cub->engine.delta.y = cub->dir.x * cub->config.movespeed;
    }
	if (cub->engine.move.right)
    {
      	cub->engine.delta.x = cub->dir.y * cub->config.movespeed;
		cub->engine.delta.y = -1 * cub->dir.x * cub->config.movespeed;
    }
	move_validation(cub, cub->engine.delta);
	cub->engine.delta.x = 0;
	cub->engine.delta.y = 0;
}

void	check_movement(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W)
		cub->engine.move.up = 1;
    if (keycode == KEY_S)
		cub->engine.move.down = 1;
	if (keycode == KEY_A)
		cub->engine.move.left = 1;
	if (keycode == KEY_D)
		cub->engine.move.right = 1;
}


int	key_down(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_ESC)
		exit_cub(cub);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		check_movement(keycode, cub);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		rotate_camera(keycode, cub);
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W)
		cub->engine.move.up = 0;
	if (keycode == KEY_S)
		cub->engine.move.down = 0;
	if (keycode == KEY_A)
		cub->engine.move.left = 0;
	if (keycode == KEY_D)
		cub->engine.move.right = 0;
	if (keycode == KEY_RIGHT)
		cub->engine.rot.right = 0;
    if (keycode == KEY_LEFT)
		cub->engine.rot.left = 0;
	return (0);
}

void	draw_floor(t_cub3d *cub, t_img *img)
{
	int	start;
	int	i;
	int	y;

	start = - 1;
	y = -1;
	while (++y < SCREEN_W)
	{
		i = start;	
		while (++i - start != SCREEN_H)
			my_mlx_pixel_put(img, y, i, cub->config.floor.rgb);
	}
}

int	update(t_cub3d *cub)
{
	init_screen_win(cub);
	raycasting(cub);
	minimap(cub);
	update_cam(cub);
	update_pos(cub);
	mlx_destroy_image(cub->mlx, cub->screen.img);
	mlx_destroy_image(cub->mlx, cub->minimap.img);
	return (0);
}

static int	create_trgb(t_rgb rgb)
{
	int	t;

	t = 0;
	return (t << 24 | rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

static t_img	init_bground(t_cub3d *cub)
{
	t_img	bground;
	t_ipos	i;
	

	cub->config.floor.rgb = create_trgb(cub->config.floor);
	cub->config.ceiling.rgb = create_trgb(cub->config.ceiling);
	bground.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	bground.addr = mlx_get_data_addr(bground.img, &bground.bpp, &bground.ll, &bground.endian);
	cub->bground = bground;
	i.x = -1;
	while (++i.x < SCREEN_W)
		ver_line(cub->bground.img, i.x, SCREEN_H, cub->config.floor.rgb);
	return (bground);
}	

void	loop(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H, "cub3d");
	init_buffer(&cub->buf, cub);
	init_textures(cub);
	init_bground(cub);
	mlx_hook(cub->win, ON_KEYDOWN, 0, key_down, cub);
	mlx_hook(cub->win, ON_KEYUP, 0, key_release, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, &update, cub);
	mlx_loop(cub->mlx);
}
