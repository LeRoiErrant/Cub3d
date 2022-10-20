#include "../includes/cub3d.h"

int	exit_cub(t_cub3d *cub)
{
	int	i;

	i = -1;
	while (++i < TEX_END)
	{
		mlx_destroy_image(cub->mlx, cub->tex[i]->img);
		free(cub->tex[i]);
	}
//	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_image(cub->mlx, cub->buf.img);
	mlx_destroy_window(cub->mlx, cub->win);
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

t_ipos	door_range(t_cub3d *cub)
{
	t_ipos	coord;
	int		loop;
	double	mult;

	
	loop = 1;
	mult = 0.1;
	coord.x = (int) (cub->pos.x + (mult * cub->ray.step.x));
	coord.y = (int) (cub->pos.y + (mult * cub->ray.step.y));
	while (loop && mult <= 1.5)
	{
		if (cub->map[coord.x][coord.y] == 'D' || cub->map[coord.x][coord.y] == 'O')
			loop = 0;
		else
		{
			mult += 0.1;
			coord.x = (int) (cub->pos.x + (mult * cub->dir.x));
			coord.y = (int) (cub->pos.y + (mult * cub->dir.y));
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

void	move_validation(t_cub3d *cub, t_dpos move)
{
	t_ipos	coord;

	coord.x = (int) (cub->pos.x + move.x);
	coord.y = (int) (cub->pos.y + move.y);
	if (cub->map[coord.x][coord.y] == '1' || cub->map[coord.x][coord.y] == 'D')
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
	if (keycode == KEY_E)
		open_door(cub);
	return (0);
}

int	mouse_move(int x, int y, t_cub3d *cub)
{
	float	rotspeed;
	float	olddirx;
	float	oldplanex;

	(void) y;
	rotspeed = ((float) (x - SCREEN_W / 2)) / 500.0;
	olddirx = cub->dir.x;
	oldplanex = cub->plane.x;
	cub->dir.x = cub->dir.x * cos(-rotspeed) - cub->dir.y * sin(-rotspeed);
	cub->dir.y = olddirx * sin(-rotspeed) + cub->dir.y * cos(-rotspeed);
	cub->plane.x = cub->plane.x * cos(-rotspeed) - cub->plane.y * sin(-rotspeed);
	cub->plane.y = oldplanex * sin(-rotspeed) + cub->plane.y * cos(-rotspeed);
	mlx_mouse_move(cub->win, (int)(SCREEN_W / 2), (int)(SCREEN_H / 2));
	return (0);
}

//TODO animation loop
int	mouse_down(int button, int x, int y, t_cub3d *cub)
{
	(void) x;
	(void) y;
	if (button == M_LEFT)
		cub->shoot = 1;
	return (SUCCESS);
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

//TODO animation loop
void	gun(t_cub3d *cub)
{	
	mlx_put_image_to_window(cub->mlx, cub->win, cub->tex[cub->gun_frame]->img, SCREEN_W / 2 - (cub->tex[cub->gun_frame]->w / 2), SCREEN_H - cub->tex[cub->gun_frame]->h);
}

void	anim_door(t_cub3d *cub)
{
	cub->framecount++;
	if (cub->framecount % 8 == 0)
	{
		if (cub->door_side < TEX_SIDE4 && !cub->appear)
			cub->door_side++;
		else if (cub->door_side == TEX_SIDE4 && !cub->appear)
			cub->appear = 1;
		else if (cub->door_side > TEX_SIDE0 && cub->appear)
			cub->door_side--;
		else if (cub->door_side == TEX_SIDE0 && cub->appear)
		{
			cub->framecount = 0;
			cub->appear = 0;
		}
	}
}

void	animation(t_cub3d *cub)
{
	anim_door(cub);
	if (cub->shoot)
	{
		cub->g_framecount++;
		if (cub->g_framecount % 8 == 0)
		{
			if (cub->gun_frame == TEX_GUN5)
			{
				cub->gun_frame = TEX_GUN0;
				cub->shoot = 0;
				cub->g_framecount = 0;
			}
			else if (cub->gun_frame < TEX_GUN5)
				cub->gun_frame++;
		}
	}
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

static int	create_trgb(t_rgb rgb)
{
	int	t;

	t = 0;
	return (t << 24 | rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

static t_img	init_bground(t_cub3d *cub)
{
	t_img	bground;
	//t_ipos	i;
	

	cub->config.floor.rgb = create_trgb(cub->config.floor);
	cub->config.ceiling.rgb = create_trgb(cub->config.ceiling);
	bground.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	bground.addr = mlx_get_data_addr(bground.img, &bground.bpp, &bground.ll, &bground.endian);
	cub->bground = bground;
	/*i.x = -1;
	while (++i.x < SCREEN_W)
		ver_line(cub->bground.img, i.x, SCREEN_H, cub->config.floor.rgb);*/
	return (bground);
}	

void	loop(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H, "cub3d");
	init_buffer(&cub->buf, cub);
	//init_textures(cub);
	init_bground(cub);
	mlx_mouse_move(cub->win, (int)(SCREEN_W / 2), (int)(SCREEN_H / 2));
	mlx_mouse_hide(cub->win);
	mlx_hook(cub->win, ON_KEYDOWN, 0, key_down, cub);
	mlx_hook(cub->win, ON_KEYUP, 0, key_release, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, exit_cub, cub);
	mlx_hook(cub->win, ON_MOUSEMOVE, 0, mouse_move, cub);
	mlx_hook(cub->win, ON_MOUSEDOWN, 0, mouse_down, cub);
	path_to_img(cub);
	cub->door_side = TEX_SIDE0;
	mlx_loop_hook(cub->mlx, &update, cub);
	mlx_loop(cub->mlx);
}
