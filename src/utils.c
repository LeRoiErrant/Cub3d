#include "../includes/cub3d.h"

//TODO update cub->errnum
int	cub_error(int errnum, int fd)
{
	if (errnum == E_FAILURE && fd > 0)
		ft_putstr_fd("Error\n", fd);
	if (errnum == E_ARGC && fd > 0)
		ft_putstr_fd("Error\nWrong argument count\n", fd);
	if (errnum == E_EXT && fd > 0)
		ft_putstr_fd("Error\nWrong config file extension\n", fd);
	if (errnum == E_MALLOC && fd > 0)
		ft_putstr_fd("Error\nCan't allocate memory\n", fd);
	if (errnum == E_OPEN && fd > 0)
		ft_putstr_fd("Error\nCan't open config file\n", fd);
	if (errnum == E_CONFIG && fd > 0)
		ft_putstr_fd("Error\nWrong config format\n", fd);
	if (errnum == E_MAP && fd > 0)
		ft_putstr_fd("Error\nWrong map config\n", fd);
	if (errnum == E_CEILING && fd > 0)
		ft_putstr_fd("Error\nWrong ceiling color config\n", fd);
	if (errnum == E_FLOOR && fd > 0)
		ft_putstr_fd("Error\nWrong floor color config\n", fd);
	if (errnum == E_PATH && fd > 0)
		ft_putstr_fd("Error\nWrong texture path config\n", fd);
	if (errnum == E_WALL && fd > 0)
		ft_putstr_fd("Error\nMap not surrounded by walls\n", fd);
	if (errnum == E_CHAR && fd > 0)
		ft_putstr_fd("Error\nWrong char in map\n", fd);
	if (errnum == E_PLAYER && fd > 0)
		ft_putstr_fd("Error\nWrong amount of player\n", fd);
	return (errnum);
}

void	cub_print(t_cub3d *cub)
{
	int	i;

	printf("\n");
	printf("F red = %d\n", cub->config.floor.red);
	printf("F green = %d\n", cub->config.floor.green);
	printf("F blue = %d\n", cub->config.floor.blue);
	printf("\n");
	printf("C red = %d\n", cub->config.ceiling.red);
	printf("C green = %d\n", cub->config.ceiling.green);
	printf("C blue = %d\n", cub->config.ceiling.blue);
	printf("\n");
	printf("path north = {%s}\n", cub->config.path_n);
	printf("path south = {%s}\n", cub->config.path_s);
	printf("path west = {%s}\n", cub->config.path_w);
	printf("path east = {%s}\n", cub->config.path_e);
	printf("\n");
	printf("pos.x = %f\npos.y = %f\n\n", cub->pos.x, cub->pos.y);
	i = -1;
	while (cub->map[++i])
		printf("%s\n", cub->map[i]);
}

int	count_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	get_map_size(char **config, t_cub3d *cub)
{
	int	i;

	i = 5;
	while (config[++i])
	{
		if (!ft_strchr_set(config[i], "01"))
			return (cub_error(E_MAP, STDERR_FILENO));
		if ((int)ft_strlen(config[i]) > cub->config.map_w)
			cub->config.map_w = ft_strlen(config[i]);
		cub->config.map_h++;
	}
	if (cub->config.map_h < 3 || cub->config.map_w < 3)
		return (cub_error(E_MAP, STDERR_FILENO));
	return (SUCCESS);
}

//TODO free tmp array
void	free_cub(t_cub3d *cub)
{
	free(cub->config.path_n);
	free(cub->config.path_s);
	free(cub->config.path_w);
	free(cub->config.path_e);
	ft_free_matrix(&cub->map);
	free(cub->tmp);
}
