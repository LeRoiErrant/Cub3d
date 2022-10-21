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

# define SCR_W 640
# define SCR_H 480

/*# define SCR_W 1920
# define SCR_H 1080*/

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
# define HEX_BLUE 0x000000FF
# define HEX_DARK_BLUE 0x000000AB

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
	ON_KEYDOWN 		= 2,	//? int (*f)(int keycode, void *param)
	ON_KEYUP 		= 3,	//? int (*f)(int keycode, void *param)
	ON_MOUSEDOWN 	= 4,	//? int (*f)(int button, int x, int y, void *param)
	ON_MOUSEUP 		= 5,	//? int (*f)(int button, int x, int y, void *param)
	ON_MOUSEMOVE 	= 6,	//? int (*f)(int x, int y, void *param)
	ON_EXPOSE 		= 12,	//? int (*f)(void *param)
	ON_DESTROY 		= 17	//? int (*f)(void *param)
};

enum e_mouse_event
{
	M_LEFT 			= 1,
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
	TEX_CLS,
	TEX_OPN0,
	TEX_OPN1,
	TEX_OPN2,
	TEX_OPN3,
	TEX_OPN4,
	TEX_SIDE0,
	TEX_SIDE1,
	TEX_SIDE2,
	TEX_SIDE3,
	TEX_SIDE4,
	TEX_GUN0,
	TEX_GUN1,
	TEX_GUN2,
	TEX_GUN3,
	TEX_GUN4,
	TEX_GUN5,
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
	t_img		gun;
	int			shoot;
	int			g_framecount;
	int			framecount;
	t_dpos		pos;
	t_dpos		pc;
	t_dpos		dir;
	t_dpos		plane;
	t_raycast	ray;
	t_texture	o_tex;
	t_img		*tex[TEX_END];
	int			door_side;
	int			appear;
	t_assets	textures;
	t_config	config;
	t_engine	engine;
	int			errnum;
	int			reset_buffer;
	int			color;
	int			gun_frame;
	t_ipos		coord_test;
}	t_cub3d;

//animations.c
void	anim_door(t_cub3d *cub);
void	animation(t_cub3d *cub);

// check_config.c
int		check_extension(char *argv);
int		check_config(t_cub3d *cub);
int		check_path(char *path);

// check_map.c
int		check_char(t_cub3d *cub, char **map, int player_count, char *set);
int		check_borders(t_cub3d *cub);

// color.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		distance_shade(int color, double distance);
int		get_tex_color(t_cub3d *cub);

// door_open.c
void	open_door(t_cub3d *cub);

// door.c
void	check_door_hit_x(t_cub3d* cub);
void	check_door_hit_y(t_cub3d* cub);
void	check_door_hit(t_cub3d *cub);
void	check_door(t_cub3d *cub, int x, int y, t_ipos d);
void	check_open_door(t_cub3d *cub, int x, int y, int side);

// config.c
int		fill_config_path(char *config, t_cub3d *cub);
int		fill_config_color(char *config, t_cub3d *cub);

// config_bonus.c
int		config_doors(t_cub3d *cub);
int		config_guns(t_cub3d *cub);

// engine.c
void	rotate_camera(int keycode, t_cub3d *cub);
void	update_cam(t_cub3d *cub);
void	move_validation(t_cub3d *cub, t_dpos move);
void	update_pos(t_cub3d *cub);
void	check_movement(int keycode, t_cub3d *cub);

// game.c
void	game(t_cub3d *cub);

// gun.c
void	gun(t_cub3d *cub);

// hooks.c
int		exit_cub(t_cub3d *cub);
int		key_down(int key, t_cub3d *cub);
int		key_release(int key, t_cub3d *cub);
int		mouse_move(int x, int y, t_cub3d *cub);
int		mouse_down(int button, int x, int y, t_cub3d *cub);

// init.c
void	init_cub(t_cub3d *cub);
t_img	init_bground(t_cub3d *cub);
int		init_tex(t_cub3d *cub);

//minimap_utils.c
void	get_start(t_cub3d *cub, t_ipos *start);
int		get_map_color(t_cub3d *cub, int x, int y);
int		is_not_in_map(t_cub3d *cub, t_ipos start, t_ipos cell);

//minimap.c
void	draw_dir(t_img *img, t_cub3d *cub);
void	draw_pc(t_img *img, int color, t_cub3d *cub);
void	draw_frame(t_img *img);
void	minimap(t_cub3d *cub);

// parsing.c
int		parsing(char **argv, t_cub3d *cub);
int		init_tex(t_cub3d *cub);

// raycasting_utils.c
double	calculate_perp_dist(t_cub3d *cub);
void	does_it_hit(t_cub3d *cub);
void	draw_column(t_cub3d *cub, int x);

// raycasting.c
void	first_step(t_cub3d *cub);
double	calculate_perp_dist(t_cub3d *cub);
void	does_it_hit(t_cub3d *cub);
int		raycasting(t_cub3d *cub);

// utils.c
int		cub_error(int errnum, int fd);
int		cub_error_free(int errnum, int fd, t_cub3d *cub);
int		free_errors(t_cub3d *cub, int ret);
void	cub_print(t_cub3d *cub);
int		count_space(char *str);
int		get_map_size(char **config, t_cub3d *cub);
void	free_cub(t_cub3d *cub);

//rgb.c
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		create_trgb(t_rgb rgb);

// screen.c
void	init_images(t_cub3d *cub);

//shapes.c
int		in_circle(float x, float y);
void 	d_cell(t_img *img, int x, int y, int color);
void 	ver_line(t_img *img, int x, int length, int color);

#endif
