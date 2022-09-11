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

//? temporary
typedef struct s_cub3d
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	void	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_cub3d;

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

























#endif