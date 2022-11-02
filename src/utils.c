/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:45:25 by 0xNino            #+#    #+#             */
/*   Updated: 2022/11/02 10:45:31 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//TODO update cub->errnum
int	cub_error(int errnum, int fd)
{
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
}

int	cub_error_free(int errnum, int fd, t_cub3d *cub)
{
	cub_error(errnum, fd);
	free_cub(cub);
	return (errnum);
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

void	free_cub(t_cub3d *cub)
{
	int	i;

	i = -1;
	while (++i < TEX_END)
	{
		if (cub->config.path[i])
			free(cub->config.path[i]);
	}
	ft_free_matrix(&cub->map);
	free(cub->tmp);
}
