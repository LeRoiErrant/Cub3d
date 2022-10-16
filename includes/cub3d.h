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

/*# define SCREEN_W 1920
# define SCREEN_H 1080*/

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

# define HEX_RED 0x00FF0000
# define HEX_DARK_RED 0x00AB0000
# define HEX_GREEN 0x0000FF00
# define HEX_DARK_GREEN 0x0000AB00

enum e_error
{
	E_SUCCESS,
	E_FAILURE,
	E_ARGC,
	E_EXT,
	E_MALLOC,
	E_OPEN,
	E_CONFIG,
	E_MAP,
	E_CEILING,
	E_FLOOR,
	E_PATH,
	E_WALL,
	E_CHAR,
	E_PLAYER,
};

enum e_key_event
{
	ON_KEYDOWN 		= 2,		//? int (*f)(int keycode, void *param)
	ON_KEYUP 		= 3,		//? int (*f)(int keycode, void *param)
	ON_MOUSEDOWN 	= 4,	//? int (*f)(int button, int x, int y, void *param)
	ON_MOUSEUP 		= 5,		//? int (*f)(int button, int x, int y, void *param)
	ON_MOUSEMOVE 	= 6,	//? int (*f)(int x, int y, void *param)
	ON_EXPOSE 		= 12,		//? int (*f)(void *param)
	ON_DESTROY 		= 17		//? int (*f)(void *param)
};

enum e_mouse_event
{
	M_LEFT 			= 2,
	M_RIGHT 		= 2,
	M_MIDDLE 		= 3,
	M_SCROLLUP 		= 4,
	M_SCROLLDOWN	= 5
};

enum e_keycode
{
	KEY_A 		= 	0,
	KEY_S 		= 	1,
	KEY_D 		= 	2,
	KEY_Q 		= 	12,
	KEY_W 		= 	13,
	KEY_E 		= 	14,
	KEY_R 		= 	15,
	KEY_SPACE 	= 	49,
	KEY_ESC 	=	53,
	KEY_LEFT 	=	123,
	KEY_RIGHT 	=	124,
	KEY_DOWN 	=	125,
	KEY_UP 		=	126
};

enum e_side
{
	SIDE_X,
	SIDE_Y
};

enum e_tex
{
	TEX_NO,
	TEX_WE,
	TEX_SO,
	TEX_EA,
	TEX_OPN,
	TEX_CLS,
	TEX_SIDE,
	TEX_END
};

typedef struct s_door
{
	int	state;
	int	tex;
}	t_door;

typedef struct s_img
{
	void	*img;

	char	*addr;		
	int		bpp;
	int		ll;
	int		endian;

	int		w;
	int		h;
}	t_img;

typedef struct s_assets
{
	t_img	*north;
	t_img	*south;
	t_img	*east;
	t_img	*west;
}	t_assets;
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

typedef struct s_move
{
	int	up;
	int	left;
	int	down;
	int	right;
}	t_move;

typedef struct s_engine
{
	t_move	move;
	t_move	rot;
	t_dpos	delta;
}	t_engine;

typedef struct s_texture
{
	int		**array;
	int		x;
	int		y;
	int		w;
	int		h;
	int		num;
	double	pos;
	double	step;
	t_dpos	wall;
	int		color;
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
	t_dpos	map;
	t_ipos	step;
	int		hit;
	int		side;
	t_door	door;
	int		line;
	t_line	line_info;
}	t_raycast;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
	int	rgb;
}	t_rgb;

typedef struct s_config
{
	double	movespeed;
	double	rotspeed;
	char	*path[TEX_END];
	t_rgb	floor;
	t_rgb	ceiling;
	int		map_w;
	int		map_h;
}	t_config;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**tmp;
	t_img		img;
	t_img		buf;
	t_img		screen;
	t_img		bground;
	t_img		minimap;
	t_dpos		pos;
	t_dpos		pc;
	t_dpos		dir;
	t_dpos		plane;
	t_raycast	ray;
	t_texture	o_tex;
	t_img		*tex[TEX_END];
	t_assets	textures;
	t_config	config;
	t_engine	engine;
	int			errnum;
	int			reset_buffer;
	int			color;
	t_ipos		coord_test;
}	t_cub3d;

// check_config.c
int		check_extension(char *argv);
int		check_config(t_cub3d *cub);
int		check_path(char *path);

//check_map.c
int		check_char(char **map, t_cub3d *cub);
int		check_borders(t_cub3d *cub);

// init.c
void	init_cub(t_cub3d *cub);
void	init_buffer(t_img *buf, t_cub3d *cub);
//void	init_textures(t_cub3d *cub);

// parsing.c
int		parsing(char **argv, t_cub3d *cub);

// mlx.c
int		exit_cub(t_cub3d *cub);
int		key_down(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);
void	loop(t_cub3d *cub);

// raycasting.c
int		raycasting(t_cub3d *cub);

// utils.c
int		cub_error(int errnum, int fd);
int		cub_error_free(int errnum, int fd, t_cub3d *cub);
int		free_errors(t_cub3d *cub, int ret);
void	cub_print(t_cub3d *cub);
int		count_space(char *str);
int		get_map_size(char **config, t_cub3d *cub);
void	free_cub(t_cub3d *cub);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	minimap(t_cub3d *cub);
void	init_engine(t_cub3d *cub);
void	init_screen_win(t_cub3d *cub);
void 	d_cell(t_img *img, int x, int y, int color);
void 	ver_line(t_img *img, int x, int length, int color);
int		distance_shade(int color, double distance);
int		path_to_img(t_cub3d *cub);
int		get_color(t_img *img, int x, int y);

#endif
