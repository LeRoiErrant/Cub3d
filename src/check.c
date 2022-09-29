#include "../includes/cub3d.h"

int	check_config(t_cub3d *cub)
{
	if (cub->config.ceiling.red < 0 || cub->config.ceiling.red > 255)
		return (cub_error(E_CEILING, STDERR_FILENO));
	if (cub->config.ceiling.green < 0 || cub->config.ceiling.green > 255)
		return (cub_error(E_CEILING, STDERR_FILENO));
	if (cub->config.ceiling.blue < 0 || cub->config.ceiling.blue > 255)
		return (cub_error(E_CEILING, STDERR_FILENO));
	if (cub->config.floor.red < 0 || cub->config.floor.red > 255)
		return (cub_error(E_FLOOR, STDERR_FILENO));
	if (cub->config.floor.green < 0 || cub->config.floor.green > 255)
		return (cub_error(E_FLOOR, STDERR_FILENO));
	if (cub->config.floor.blue < 0 || cub->config.floor.blue > 255)
		return (cub_error(E_FLOOR, STDERR_FILENO));
	if (!cub->config.path_n || !cub->config.path_s)
		return (cub_error(E_PATH, STDERR_FILENO));
	if (!cub->config.path_w || !cub->config.path_e)
		return (cub_error(E_PATH, STDERR_FILENO));
	return (SUCCESS);
}

int	check_char(char **map, t_cub3d *cub)
{
	int		i;
	int		j;
	int		player_count;
	char	*set;

	player_count = 0;
	i = 5;
	set = " 01NSEW";
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(set, map[i][j]))
				return (cub_error(E_CHAR, STDERR_FILENO));
			if (ft_strchr(set + 3, map[i][j]))
			{
				cub->pos.x = i - 6;
				cub->pos.y = j;
				player_count++;
			}
		}
	}
	if (player_count != 1)
		return (cub_error(E_PLAYER, STDERR_FILENO));
	return (SUCCESS);
}

static int	check_walls(t_cub3d *cub)
{
	int	i;
	int	j;
	int	check;

	check = SUCCESS;
	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '.')
			{
				if (j >= 1)
					check += cub->map[i][j - 1] == '0';
				if (j < cub->config.map_w - 1)
					check += cub->map[i][j + 1] == '0';
				if (i >= 1)
					check += cub->map[i - 1][j] == '0';
				if (i < cub->config.map_h - 1)
					check += cub->map[i + 1][j] == '0';
			}
		}
	}
	return (check);
}

int	check_map(t_cub3d *cub)
{
	int	i;
	int	j;

	if (!*cub->map)
		return (cub_error(E_MAP, STDERR_FILENO));
	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[0][++j])
			if (cub->map[0][j] == '0')
				return (cub_error(E_MAP, STDERR_FILENO));
		j = -1;
		while (cub->map[cub->config.map_h - 1][++j])
			if (cub->map[cub->config.map_h - 1][j] == '0')
				return (cub_error(E_MAP, STDERR_FILENO));
	}
	if (check_walls(cub))
		return (cub_error(E_WALL, STDERR_FILENO));
	return (SUCCESS);
}
