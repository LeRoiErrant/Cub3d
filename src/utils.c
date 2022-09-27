#include "../includes/cub3d.h"

int	cub_error(int errnum, int fd)
{
	if (errnum == E_FAILURE && fd > 0)
		ft_putstr_fd("Error\n", STDERR_FILENO);
	if (errnum == E_MALLOC && fd > 0)
		ft_putstr_fd("Error\nmalloc() failed\n", STDERR_FILENO);
	if (errnum == E_OPEN && fd > 0)
		ft_putstr_fd("Error\nopen() failed\n", STDERR_FILENO);
	if (errnum == E_ARGC && fd > 0)
		ft_putstr_fd("Error\nwrong argument count\n", STDERR_FILENO);
	if (errnum == E_CONFIG && fd > 0)
		ft_putstr_fd("Error\nWrong config format\n", STDERR_FILENO);
	if (errnum == E_MAP && fd > 0)
		ft_putstr_fd("Error\nWrong map format\n", STDERR_FILENO);
	if (errnum == E_CEILING && fd > 0)
		ft_putstr_fd("Error\nWrong ceiling color format\n", STDERR_FILENO);
	if (errnum == E_FLOOR && fd > 0)
		ft_putstr_fd("Error\nWrong floor color format\n", STDERR_FILENO);
	return (errnum);
}

void	cub_print(t_cub3d *cub)
{
	int i;

	printf("F red = %d\n", cub->config.floor.red);
	printf("F green = %d\n", cub->config.floor.green);
	printf("F blue = %d\n", cub->config.floor.blue);
	printf("C red = %d\n", cub->config.ceiling.red);
	printf("C green = %d\n", cub->config.ceiling.green);
	printf("C blue = %d\n", cub->config.ceiling.blue);
	printf("path north = {%s}\n", cub->config.path_n);
	printf("path south = {%s}\n", cub->config.path_s);
	printf("path west = {%s}\n", cub->config.path_w);
	printf("path east = {%s}\n", cub->config.path_e);
	i = -1;
	while (cub->map[++i])
		printf("map[%d] =\t{%s}\n", i, cub->map[i]);
}

int	count_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void	get_map_size(char **config, t_cub3d *cub)
{
	int	i;

	i = 5;
	while (config[++i])
	{
		if ((int)ft_strlen(config[i]) > cub->config.map_w)
			cub->config.map_w = ft_strlen(config[i]);
		cub->config.map_h++;
	}
}
