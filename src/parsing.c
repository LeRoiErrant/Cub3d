#include "../includes/cub3d.h"

static int	count_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

static void	fill_path(char *config, t_cub3d *cub)
{
	if (!ft_strncmp(config, "NO", 2))
		cub->config.path_n = ft_strtrim(config + 2, " ");
	else if (!ft_strncmp(config, "SO", 2))
		cub->config.path_s = ft_strtrim(config + 2, " ");
	else if (!ft_strncmp(config, "WE", 2))
		cub->config.path_w = ft_strtrim(config + 2, " ");
	else if (!ft_strncmp(config, "EA", 2))
		cub->config.path_e = ft_strtrim(config + 2, " ");
}

static void	fill_color(char *config, t_cub3d *cub)
{
	char **tmp;

	if (!ft_strncmp(config, "F", 1))
	{
		tmp = ft_split(config + 1, ',');
		if (ft_matrixlen(tmp) == 3)
		{
			cub->config.floor.red = ft_atoi(tmp[0]);
			cub->config.floor.green = ft_atoi(tmp[1]);
			cub->config.floor.blue = ft_atoi(tmp[2]);
		}
		ft_free_double_ptr((void ***)&tmp);
	}
	else if (!ft_strncmp(config, "C", 1))
	{
		tmp = ft_split(config + 1, ',');
		if (ft_matrixlen(tmp) == 3)
		{
			cub->config.ceiling.red = ft_atoi(tmp[0]);
			cub->config.ceiling.green = ft_atoi(tmp[1]);
			cub->config.ceiling.blue = ft_atoi(tmp[2]);
		}
		ft_free_double_ptr((void ***)&tmp);
	}
}

int	fill_config(char **config, t_cub3d *cub)
{
	int	i;

	i = -1;
	while (config[++i] && i < 6)
	{
		config[i] += count_space(config[i]);
		fill_path(config[i], cub);
		fill_color(config[i], cub);
	}
	if (i < 6)
		return (FAILURE);
	else
		return (SUCCESS);
}

int	fill_map(char **config, t_cub3d *cub)
{
	int	i;

	i = -1;
	cub->map = (char **) ft_calloc(ft_matrixlen(config) - 5, sizeof(char *));
	while (config[++i + 6])
		cub->map[i] = ft_strdup(config[i + 6]);
	return (SUCCESS);
}

//TODO error handling
int	parse_file(char **argv, t_cub3d *cub)
{
	int		fd;
	char	*str;
	char	*tmp;
	char	**config;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (cub_error(E_OPEN, STDERR_FILENO));
	str = strdup("");
	while (str)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (tmp && ft_strcmp(tmp, "\n"))
			str = ft_strjoin_free(str, tmp);
	}
	if (!str)
		return (FAILURE);
	config = ft_split(str, '\n');
	if (fill_config(config, cub))
		return (cub_error(E_CONFIG, STDERR_FILENO));
	fill_map(config, cub);
	cub_print(cub);
	return (0);
}
