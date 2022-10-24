#include "../includes/cub3d.h"

static int	fill_config(char **config, t_cub3d *cub)
{
	int	i;

	i = -1;
	while (config[++i] && i < 6)
	{
		config[i] += count_space(config[i]);
		if (fill_config_path(config[i], cub))
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

static void	fill_map_space(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == ' ')
				map[i][j] = '.';
	}
}

static int	fill_map(char **config, t_cub3d *cub)
{
	int	i;

	if (get_map_size(config, cub))
		return (cub_error(E_MAP, -1));
	if (check_char(cub, config, 0, " 01DONSEW"))
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
	fill_map_space(cub->map);
	return (check_borders(cub));
}

int	parsing(char **argv, t_cub3d *cub)
{
	int		fd;
	char	*str;
	char	*line;

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
	return (SUCCESS);
}
