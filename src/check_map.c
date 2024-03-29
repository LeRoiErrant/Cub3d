/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:43:46 by 0xNino            #+#    #+#             */
/*   Updated: 2022/11/02 10:43:47 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_initial_direction(t_cub3d *cub, char pc)
{
	if (pc == 'N')
	{
		cub->dir.x = -1.0;
		cub->plane.y = 0.66;
	}
	else if (pc == 'S')
	{
		cub->dir.x = 1.0;
		cub->plane.y = -0.66;
	}
	else if (pc == 'E')
	{
		cub->dir.y = 1.0;
		cub->plane.x = 0.66;
	}
	else
	{
		cub->dir.y = -1.0;
		cub->plane.x = -0.66;
	}
}

int	check_char(t_cub3d *cub, char **map, int player_count, char *set)
{
	int		i;
	int		j;

	i = 5;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(set, map[i][j]))
				return (cub_error(E_CHAR, STDERR_FILENO));
			if (ft_strchr(set + 5, map[i][j]))
			{
				cub->pos.x = i - 6 + 0.5;
				cub->pos.y = j + 0.5;
				get_initial_direction(cub, map[i][j]);
				cub->pc.x = cub->pos.x * 10;
				cub->pc.y = cub->pos.y * 10;
				player_count++;
			}
		}
	}
	if (player_count != 1)
		return (cub_error(E_PLAYER, STDERR_FILENO));
	return (SUCCESS);
}

static int	check_spaces(t_cub3d *cub)
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

static int	check_player(t_cub3d *cub)
{
	int	i;
	int	j;
	int	check;

	i = cub->pos.x;
	j = cub->pos.y;
	check = SUCCESS;
	if (j >= 1)
		check += cub->map[i][j - 1] == '.';
	if (j < cub->config.map_w - 1)
		check += cub->map[i][j + 1] == '.';
	if (i >= 1)
		check += cub->map[i - 1][j] == '.';
	if (i < cub->config.map_h - 1)
		check += cub->map[i + 1][j] == '.';
	return (check);
}

int	check_borders(t_cub3d *cub)
{
	int	i;

	if (!*cub->map)
		return (cub_error(E_MAP, STDERR_FILENO));
	i = -1;
	while (++i < cub->config.map_w)
		if (cub->map[0][i] == '0' || cub->map[cub->config.map_h - 1][i] == '0')
			return (cub_error(E_WALL, STDERR_FILENO));
	i = -1;
	while (++i < cub->config.map_h)
		if (cub->map[i][0] == '0' || cub->map[i][cub->config.map_w - 1] == '0')
			return (cub_error(E_WALL, STDERR_FILENO));
	if (check_spaces(cub))
		return (cub_error(E_WALL, STDERR_FILENO));
	if (check_player(cub))
		return (cub_error(E_WALL, STDERR_FILENO));
	return (SUCCESS);
}
