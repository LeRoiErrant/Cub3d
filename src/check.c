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
	return (SUCCESS);
}

//TODO check if map is open
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
	return (SUCCESS);
}
