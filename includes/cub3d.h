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

# define SCREEN_W 640
# define SCREEN_H 480

# define TEXTURE_W 64
# define TEXTURE_H 64

# define SUCCESS 0
# define FAILURE 1

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

# define GR "\033[32;1m"
# define RE "\033[31;1m"
# define YE "\033[33;1m"
# define CY "\033[36;1m"
# define RC "\033[0m"

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
	void	*ptr;

	char	*addr;		
	int		bpp;
	int		ll;
	int		endian;

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
	double		perpwalldist;
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
	int		map_w;
	int		map_h;
}	t_config;

typedef enum s_error
{
	E_SUCCESS,
	E_FAILURE,
	E_MALLOC,
	E_OPEN,
	E_ARGC,
	E_CONFIG,
	E_MAP,
	E_CEILING,
	E_FLOOR,
	E_PATH,
	E_WALL,
}	t_error;

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
	t_error		errnum;
	int			buffer[SCREEN_H][SCREEN_W];
	int			reset_buffer;
	char		**map;
	char		**tmp;
}	t_cub3d;

// check.c
int		check_config(t_cub3d *cub);
int		check_map(t_cub3d *cub);

// init.c
void	init_config(t_cub3d *cub);
void	init_cub(t_cub3d *cub);

// parsing.c
int		parsing(char **argv, t_cub3d *cub);

// mlx.c
int		esc_win(t_cub3d *cub);
int		key_event(int key, t_cub3d *cub);
int		key_hook(t_cub3d *cub);

// utils.c
int		cub_error(int errnum, int fd);
void	cub_print(t_cub3d *cub);
int		count_space(char *str);
void	get_map_size(char **config, t_cub3d *cub);
void	free_cub(t_cub3d *cub);

#endif
