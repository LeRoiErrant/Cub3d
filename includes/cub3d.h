#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/include/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdint.h>

#define SCREEN_W	640
#define SCREEN_H	480
#define TEXTURE_W	64
#define TEXTURE_H	64

typedef struct s_mlx
{
	void	*ptr;
}	t_mlx;

typedef struct s_win
{
	void	*ptr;
}	t_win;

typedef struct s_img
{
	//mlx_init
	void	*ptr;

	//mlx_get_data_addr
	char	*addr;		
	int		bpp;
	int		line_len;
	int		endian;

	//mlx_xpm_file_to_image
	int		width;
	int		height;
}	t_img;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_dir
{
	double	x;
	double	y;
	double	angle;
}	t_dir;

typedef struct s_plane
{
	double	x;
	double	y;
}	t_plane;

typedef struct s_texture
{
	int		**array;
	int		x;
	int		y;
	int		num;
	double	pos;
}	t_texture;

typedef struct s_ray
{
	t_dir	dir;
}	t_ray;

typedef struct s_cub3d
{
	t_mlx		mlx;
	t_win		win;
	t_img		img;
	t_pos		pos;
	t_dir		dir;
	t_plane		plane;
	t_texture	texture;
	int			buffer[SCREEN_H][SCREEN_W];
	double		move_speed;
	double		rot_speed;
	int			reset_buffer;
}	t_cub3d;

























#endif