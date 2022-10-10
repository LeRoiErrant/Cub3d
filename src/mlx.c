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

int	key_down(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_ESC)
		exit_cub(cub);
	if (keycode == KEY_UP)
    {
      	cub->pos.x += cub->dir.x * cub->config.movespeed;
		cub->pos.y += cub->dir.y * cub->config.movespeed;
		cub->pc.x = cub->pos.x * 10;
		cub->pc.y = cub->pos.y * 10;
		printf("X: %f | Y: %f\n   pc.x: %i | pc.y: %i\n", cub->pos.x, cub->pos.y, (int) cub->pc.x, (int) cub->pc.y);
	  /*if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;*/
    }
    //move backwards if no wall behind you
    if (keycode == KEY_DOWN)
    {
      	cub->pos.x -= cub->dir.x * cub->config.movespeed;
		cub->pos.y -= cub->dir.y * cub->config.movespeed;
		cub->pc.x = cub->pos.x * 10;
		cub->pc.y = cub->pos.y * 10;
		printf("X: %f | Y: %f\n   pc.x: %i | pc.y: %i\n", cub->pos.x, cub->pos.y, (int) cub->pc.x, (int) cub->pc.y);
	 /*if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;*/
    }
	if (keycode == KEY_RIGHT)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(-cub->config.rotspeed) - cub->dir.y * sin(-cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(-cub->config.rotspeed) + cub->dir.y * cos(-cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(-cub->config.rotspeed) - cub->plane.y * sin(-cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(-cub->config.rotspeed) + cub->plane.y * cos(-cub->config.rotspeed);
    }
    //rotate to the left
    if (keycode == KEY_LEFT)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = cub->dir.x;
      cub->dir.x = cub->dir.x * cos(cub->config.rotspeed) - cub->dir.y * sin(cub->config.rotspeed);
      cub->dir.y = oldDirX * sin(cub->config.rotspeed) + cub->dir.y * cos(cub->config.rotspeed);
      double oldPlaneX = cub->plane.x;
      cub->plane.x = cub->plane.x * cos(cub->config.rotspeed) - cub->plane.y * sin(cub->config.rotspeed);
      cub->plane.y = oldPlaneX * sin(cub->config.rotspeed) + cub->plane.y * cos(cub->config.rotspeed);
    }
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	(void) keycode;
	(void) cub;
	return (0);
}

int	update(t_cub3d *cub)
{
	raycasting(cub);
	minimap(cub);
	return (0);
}

void	loop(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H, "cub3d");
	init_buffer(&cub->buf, cub);
	init_textures(cub);
	mlx_hook(cub->win, ON_KEYDOWN, 0, key_down, cub);
	mlx_hook(cub->win, ON_KEYUP, 0, key_release, cub);
	mlx_hook(cub->win, ON_DESTROY, 0, exit_cub, cub);
	mlx_loop_hook(cub->mlx, &update, cub);
	mlx_loop(cub->mlx);
}
