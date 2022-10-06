#include "../includes/cub3d.h"

int	init_errors(t_cub3d *cub)
{
	int	check;

	cub->error.msg = malloc(E_END * sizeof(*cub->error.msg));
	cub->error.msg[E_FAILURE] = ft_strdup("");
	cub->error.msg[E_ARGC] = ft_strdup("Wrong argument count\n");
	cub->error.msg[E_EXT] = ft_strdup("Wrong config file extension\n");
	cub->error.msg[E_MALLOC] = ft_strdup("Can't allocate memory\n");
	cub->error.msg[E_OPEN] = ft_strdup("Can't open config file\n");
	cub->error.msg[E_CONFIG] = ft_strdup("Wrong config format\n");
	cub->error.msg[E_MAP] = ft_strdup("Wrong map format\n");
	cub->error.msg[E_CEILING] = ft_strdup("Wrong ceiling color config\n");
	cub->error.msg[E_FLOOR] = ft_strdup("Wrong floor color config\n");
	cub->error.msg[E_PATH] = ft_strdup("Wrong texture path config\n");
	cub->error.msg[E_WALL] = ft_strdup("Map not surrounded by walls\n");
	cub->error.msg[E_CHAR] = ft_strdup("Wrong char in map\n");
	cub->error.msg[E_PLAYER] = ft_strdup("Wrong amount of player\n");
	check = E_SUCCESS;
	while (++check < E_END) 
	{
		if (!cub->error.msg[check])
			return (free_errors(cub, E_MALLOC));
	}
	return (E_SUCCESS);
}

int	free_errors(t_cub3d *cub, int ret)
{
	int	current;

	current = E_SUCCESS;
	if(cub->error.msg)
	{
		while (++current < E_END && cub->error.msg[current])
			free(cub->error.msg[current]);
		free (cub->error.msg);
	}
	return (ret);
}

//TODO update cub->errnum


int	cub_error(int errnum, int fd, t_cub3d *cub)
{
	int	errcode;

	errcode = E_FAILURE;
	if (fd > 0 && errnum != E_SUCCESS)
	{
		ft_putstr_fd("Error\n", fd);
		while (errnum != errcode && errcode < E_END)
			errcode++;
		if (errcode == E_END)
			ft_putstr_fd("Unknown error\n", fd);
		else
			ft_putstr_fd(cub->error.msg[errcode], fd);
	}
	if (errnum == E_ARGC)
		free_errors(cub, errnum);
	return (errnum);
}


/*int	cub_error(int errnum, int fd)
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
		ft_putstr_fd("Error\nWrong map format\n", fd);
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
}*/

int	cub_error_free(int errnum, int fd, t_cub3d *cub)
{
	cub_error(errnum, fd, cub);
	free_cub(cub);
	return (errnum);
}