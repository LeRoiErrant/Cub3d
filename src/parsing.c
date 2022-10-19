#include "../includes/cub3d.h"

void	load_tex(t_cub3d *cub, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->w, &tex->h);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->ll, &tex->endian);
	printf("tex: %s bpp: %i ll: %i endian: %i\n", path, tex->bpp, tex->ll, tex->endian);
}

int	path_to_img(t_cub3d *cub)
{
	int	i;
	int	check;

	i = -1;
	check = SUCCESS;
	while (++i < TEX_END)
	{
		cub->tex[i] = ft_calloc(1, sizeof(t_img));
		load_tex(cub, cub->tex[i], cub->config.path[i]);
	}
	return (check);
}

static int	fill_config_path(char *config, t_cub3d *cub)
{	
	if (!ft_strncmp(config, "NO", 2))
	{
		cub->config.path[TEX_NO] = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path[TEX_NO]), STDERR_FILENO));
	}
	else if (!ft_strncmp(config, "SO", 2))
	{
		cub->config.path[TEX_SO] = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path[TEX_SO]), STDERR_FILENO));
	}
	else if (!ft_strncmp(config, "WE", 2))
	{
		cub->config.path[TEX_WE] = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path[TEX_WE]), STDERR_FILENO));
	}
	else if (!ft_strncmp(config, "EA", 2))
	{
		cub->config.path[TEX_EA] = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path[TEX_EA]), STDERR_FILENO));
	}
	return (SUCCESS);
}

static void	fill_colors(t_rgb *color, char	**config)
{
	color->red = ft_atoi(config[0]);
	color->green = ft_atoi(config[1]);
	color->blue = ft_atoi(config[2]);
}

//TODO free tmp
static void	fill_config_color(char *config, t_cub3d *cub)
{
	char		**tmp;
	int			i;

	i = -1;
	if (!ft_strncmp(config, "F", 1))
	{
		tmp = ft_split(config + 1, ',');
		while (++i < 3 && tmp[i])
			tmp[i] = ft_strtrim(tmp[i], " ");
		//tmp = ft_matrixtrim_free(tmp, " ");
		if (ft_matrixlen(tmp) == 3 && ft_matrix_isnumber(tmp))
			fill_colors(&(cub->config.floor), tmp);
//		ft_free_double_ptr((void ***)&tmp);
	}
	else if (!ft_strncmp(config, "C", 1))
	{
		tmp = ft_split(config + 1, ',');
		//tmp = ft_matrixtrim_free(tmp, " ");
		while (++i < 3 && tmp[i])
			tmp[i] = ft_strtrim(tmp[i], " ");
		if (ft_matrixlen(tmp) == 3 && ft_matrix_isnumber(tmp))
			fill_colors(&(cub->config.ceiling), tmp);
//		ft_free_double_ptr((void ***)&tmp);
	}
}

static int	config_doors(t_cub3d *cub)
{
	cub->config.path[TEX_CLS] = ft_strdup("./assets/vheran/42/closed.xpm");
	if (check_path(cub->config.path[TEX_CLS]))
		return (E_PATH);
	cub->config.path[TEX_OPN] = ft_strdup("./assets/vheran/42/open.xpm");
	if (check_path(cub->config.path[TEX_OPN]))
		return (E_PATH);
	cub->config.path[TEX_SIDE] = ft_strdup("./assets/vheran/42/side.xpm");
	if (check_path(cub->config.path[TEX_SIDE]))
		return (E_PATH);
	return (SUCCESS);
}

static int	config_guns(t_cub3d *cub)
{
	cub->config.path[TEX_GUN0] = ft_strdup("./assets/weapons/gun00.xpm");
	if (check_path(cub->config.path[TEX_GUN0]))
		return (E_PATH);
	cub->config.path[TEX_GUN1] = ft_strdup("./assets/weapons/gun01.xpm");
	if (check_path(cub->config.path[TEX_GUN1]))
		return (E_PATH);
	cub->config.path[TEX_GUN2] = ft_strdup("./assets/weapons/gun02.xpm");
	if (check_path(cub->config.path[TEX_GUN2]))
		return (E_PATH);
	cub->config.path[TEX_GUN3] = ft_strdup("./assets/weapons/gun03.xpm");
	if (check_path(cub->config.path[TEX_GUN3]))
		return (E_PATH);
	cub->config.path[TEX_GUN4] = ft_strdup("./assets/weapons/gun04.xpm");
	if (check_path(cub->config.path[TEX_GUN4]))
		return (E_PATH);
	cub->config.path[TEX_GUN5] = ft_strdup("./assets/weapons/gun05.xpm");
	if (check_path(cub->config.path[TEX_GUN5]))
		return (E_PATH);
	return (SUCCESS);
}

static int	fill_config(char **config, t_cub3d *cub)
{
	int	i;

	i = -1;
	while (config[++i] && i < 6)
	{
		config[i] += count_space(config[i]);
		if(fill_config_path(config[i], cub))
			return (E_PATH);
		fill_config_color(config[i], cub);
	}
	if (config_doors(cub))
		return (E_PATH);
	if (config_guns(cub))
		return (E_PATH);
	if (i < 6)
		return (cub_error(E_CONFIG, STDERR_FILENO));
	return (check_config(cub));
}

static int	fill_map(char **config, t_cub3d *cub)
{
	int	i;
	int	j;

	if (get_map_size(config, cub))
		return (cub_error(E_MAP, -1));
	if (check_char(config, cub))
		return (cub_error(E_CHAR, -1));
	cub->map = (char **) ft_calloc(cub->config.map_h + 1, sizeof(char *));
	if (!cub->map)
		return (cub_error(E_MALLOC, -1));
	i = -1;
	while (++i < cub->config.map_h)
	{
		cub->map[i] = ft_calloc(cub->config.map_w + 1, sizeof(char));
		if (!cub->map[i])
			return (E_MALLOC);
		ft_memset(cub->map[i], '.', cub->config.map_w);
		ft_memcpy(cub->map[i], config[i + 6], ft_strlen(config[i + 6]));
	}
	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
			if (cub->map[i][j] == ' ')
				cub->map[i][j] = '.';
	}
	return (check_borders(cub));
}

//TODO handle player start direction // fix leaks of cub->tmp
int	parsing(char **argv, t_cub3d *cub)
{
	int		fd;
	char	*str;
	char	*line;

	if (check_extension(argv[1]))
		return (cub_error(E_EXT, STDERR_FILENO));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (cub_error(E_OPEN, STDERR_FILENO));
	str = NULL;
	line = get_next_line(fd);
	while (line)
	{
		str = ft_strjoin_free(str, line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!str)
		return (cub_error(E_CONFIG, STDERR_FILENO));
	cub->tmp = ft_split(str, '\n');
	free(str);
	if (fill_config(cub->tmp, cub))
		return (cub_error(E_CONFIG, -1));
	if (fill_map(cub->tmp, cub))
		return (cub_error(E_MAP, -1));
	//path_to_img(cub);
	cub_print(cub);
	return (SUCCESS);
}
