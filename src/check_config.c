#include "../includes/cub3d.h"

int	check_extension(char *argv)
{
	char	*extension;

	extension = ft_strrchr(argv, '.');
	if (extension && ft_strcmp(extension, ".cub"))
		return (E_EXT);
	return (SUCCESS);
}

int	check_config(t_cub3d *cub)
{
	if (cub->config.ceiling.red < 0 || cub->config.ceiling.red > 255)
		return (cub_error(E_CEILING, STDERR_FILENO, cub));
	if (cub->config.ceiling.green < 0 || cub->config.ceiling.green > 255)
		return (cub_error(E_CEILING, STDERR_FILENO, cub));
	if (cub->config.ceiling.blue < 0 || cub->config.ceiling.blue > 255)
		return (cub_error(E_CEILING, STDERR_FILENO, cub));
	if (cub->config.floor.red < 0 || cub->config.floor.red > 255)
		return (cub_error(E_FLOOR, STDERR_FILENO, cub));
	if (cub->config.floor.green < 0 || cub->config.floor.green > 255)
		return (cub_error(E_FLOOR, STDERR_FILENO, cub));
	if (cub->config.floor.blue < 0 || cub->config.floor.blue > 255)
		return (cub_error(E_FLOOR, STDERR_FILENO, cub));
	if (!cub->config.path_n || !cub->config.path_s)
		return (cub_error(E_PATH, STDERR_FILENO, cub));
	if (!cub->config.path_w || !cub->config.path_e)
		return (cub_error(E_PATH, STDERR_FILENO, cub));
	return (SUCCESS);
}

int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (E_PATH);
	close(fd);
	return (SUCCESS);
}
