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

#define SCREEN_W 640
#define SCREEN_H 480

#define TEXTURE_W 64
#define TEXTURE_H 64

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
	//mlx_new_image
	void	*ptr;

	//mlx_get_data_addr
	char	*addr;		
	int		bpp;
	int		ll;
	int		endian;

	//mlx_xpm_file_to_image
	int		width;
	int		height;
}	t_img;

typedef struct s_dpos
{
	double	x;
	double	y;
}	t_dpos;

typedef struct s_ipos
{
	int	x;
	int	y;
}	t_ipos;

typedef struct s_texture
{
	int		**array;
	int		x;
	int		y;
	int		num;
	double	pos;
	double	step;
	t_dpos	wall;
}	t_texture;

typedef struct s_line
{
	int			height;
	int			drawstart;
	int			drawend;
	double		perpWalldist;
	t_texture	tex_info;
}	t_line;

typedef struct s_raycast
{
	t_dpos	sidedist;
	t_dpos	raydir;
	t_dpos	deltadist;
	t_dpos	camera;
	t_ipos	map;
	t_ipos	step;
	int		hit;
	int		side;
	int		line;
	t_line	line_info;
}	t_raycast;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_config
{
	double	movespeed;
	double	rotspeed;
	char	*path_n;
	char	*path_s;
	char	*path_w;
	char	*path_e;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_config;

typedef struct s_cub3d
{
	t_mlx		mlx;
	t_win		win;
	t_img		img;
	t_dpos		pos;
	t_dpos		dir;
	t_dpos		plane;
	t_texture	tex;
	t_config	config;
	int			buffer[SCREEN_H][SCREEN_W];
	int			reset_buffer;
	char		**map;
}	t_cub3d;

























#endif