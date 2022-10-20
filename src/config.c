#include "../includes/cub3d.h"

int	fill_config_path(char *config, t_cub3d *cub)
{	
	if (!ft_strncmp(config, "NO", 2))
	{
		cub->config.path[TEX_NO] = ft_strtrim(config + 2, " ");
		return (cub_error(check_path(cub->config.path[TEX_NO]), STDERR_FILENO));
	}
	else if (!ft_strncmp(config, "SO", 2))
	{
		cub->config.path[TEX_SO] = ft_strtrim(config + 2, " ");
		return (cub_error(check_path(cub->config.path[TEX_SO]), STDERR_FILENO));
	}
	else if (!ft_strncmp(config, "WE", 2))
	{
		cub->config.path[TEX_WE] = ft_strtrim(config + 2, " ");
		return (cub_error(check_path(cub->config.path[TEX_WE]), STDERR_FILENO));
	}
	else if (!ft_strncmp(config, "EA", 2))
	{
		cub->config.path[TEX_EA] = ft_strtrim(config + 2, " ");
		return (cub_error(check_path(cub->config.path[TEX_EA]), STDERR_FILENO));
	}
	return (SUCCESS);
}

static void	fill_colors(t_rgb *color, char	**config)
{
	color->red = ft_atoi(config[0]);
	color->green = ft_atoi(config[1]);
	color->blue = ft_atoi(config[2]);
}

int	fill_config_color(char *config, t_cub3d *cub)
{
	char		**tmp;
	int			i;

	i = -1;
	if (!ft_strncmp(config, "F", 1))
	{
		tmp = ft_split(config + 1, ',');
		if (!tmp)
			return (cub_error(E_MALLOC, STDERR_FILENO));
		while (++i < 3 && tmp[i])
			tmp[i] = ft_strtrim(tmp[i], " ");
		if (ft_matrixlen(tmp) == 3 && ft_matrix_isnumber(tmp))
			fill_colors(&(cub->config.floor), tmp);
	}
	else if (!ft_strncmp(config, "C", 1))
	{
		tmp = ft_split(config + 1, ',');
		if (!tmp)
			return (cub_error(E_MALLOC, STDERR_FILENO));
		while (++i < 3 && tmp[i])
			tmp[i] = ft_strtrim(tmp[i], " ");
		if (ft_matrixlen(tmp) == 3 && ft_matrix_isnumber(tmp))
			fill_colors(&(cub->config.ceiling), tmp);
	}
	return (SUCCESS);
}