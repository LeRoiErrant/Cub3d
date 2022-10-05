#include "../includes/cub3d.h"

static int	fill_config_path(char *config, t_cub3d *cub)
{	
	if (!ft_strncmp(config, "NO", 2))
	{
		cub->config.path_n = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path_n), STDERR_FILENO, cub));
	}
	else if (!ft_strncmp(config, "SO", 2))
	{
		cub->config.path_s = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path_s), STDERR_FILENO, cub));
	}
	else if (!ft_strncmp(config, "WE", 2))
	{
		cub->config.path_w = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path_w), STDERR_FILENO, cub));
	}
	else if (!ft_strncmp(config, "EA", 2))
	{
		cub->config.path_e = ft_strtrim(config + 2, " ");
		return(cub_error(check_path(cub->config.path_e), STDERR_FILENO, cub));
	}
	return (SUCCESS);
}

//TODO free tmp
static void	fill_config_color(char *config, t_cub3d *cub)
{
	char	**tmp;

	if (!ft_strncmp(config, "F", 1))
	{
		tmp = ft_split(config + 1, ',');
		tmp = ft_matrixtrim_free(tmp, " ");
		if (ft_matrixlen(tmp) == 3 && ft_matrix_isnumber(tmp))
		{
			cub->config.floor.red = ft_atoi(tmp[0]);
			cub->config.floor.green = ft_atoi(tmp[1]);
			cub->config.floor.blue = ft_atoi(tmp[2]);
		}
//		ft_free_double_ptr((void ***)&tmp);
	}
	else if (!ft_strncmp(config, "C", 1))
	{
		tmp = ft_split(config + 1, ',');
		tmp = ft_matrixtrim_free(tmp, " ");
		if (ft_matrixlen(tmp) == 3 && ft_matrix_isnumber(tmp))
		{
			cub->config.ceiling.red = ft_atoi(tmp[0]);
			cub->config.ceiling.green = ft_atoi(tmp[1]);
			cub->config.ceiling.blue = ft_atoi(tmp[2]);
		}
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
		return (cub_error(E_CONFIG, STDERR_FILENO, cub));
	return (check_config(cub));
}

static int	fill_map(char **config, t_cub3d *cub)
{
	int	i;
	int	j;

	if (get_map_size(config, cub))
		return (cub_error(E_MAP, -1, cub));
	if (check_char(config, cub))
		return (cub_error(E_CHAR, -1, cub));
	cub->map = (char **) ft_calloc(cub->config.map_h + 1, sizeof(char *));
	if (!cub->map)
		return (cub_error(E_MALLOC, -1, cub));
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
		return (cub_error(E_EXT, STDERR_FILENO, cub));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (cub_error(E_OPEN, STDERR_FILENO, cub));
	str = NULL;
	line = get_next_line(fd);
	while (line)
	{
		str = ft_strjoin_free(str, line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!str)
		return (cub_error(E_CONFIG, STDERR_FILENO, cub));
	cub->tmp = ft_split(str, '\n');
	free(str);
	if (fill_config(cub->tmp, cub))
		return (cub_error(E_CONFIG, -1, cub));
	if (fill_map(cub->tmp, cub))
		return (cub_error(E_MAP, -1, cub));
	cub_print(cub);
	return (SUCCESS);
}
