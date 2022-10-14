#include "../includes/cub3d.h"

void	load_tex(t_cub3d *cub, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->w, &tex->h);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->ll, &tex->endian);
}

void	path_to_img(t_cub3d *cub)
{
	int	i;

	i = -1;
	while (++i < TEX_END)
	{
		cub->tex[i] = ft_calloc(1, sizeof(t_img));
		load_tex(cub, cub->tex[i], cub->config.path[i]);
	}
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
