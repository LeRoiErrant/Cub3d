/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:43:41 by 0xNino            #+#    #+#             */
/*   Updated: 2022/11/02 10:43:42 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!cub->config.path[TEX_NO] || !cub->config.path[TEX_SO])
		return (cub_error(E_PATH, STDERR_FILENO));
	if (!cub->config.path[TEX_WE] || !cub->config.path[TEX_EA])
		return (cub_error(E_PATH, STDERR_FILENO));
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
