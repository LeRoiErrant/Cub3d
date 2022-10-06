#include "../includes/cub3d.h"

void	cub_print(t_cub3d *cub)
{
	int	i;

	printf("\n");
	printf("F red =\t\t%d\n", cub->config.floor.red);
	printf("F green =\t%d\n", cub->config.floor.green);
	printf("F blue =\t%d\n", cub->config.floor.blue);
	printf("\n");
	printf("C red =\t\t%d\n", cub->config.ceiling.red);
	printf("C green =\t%d\n", cub->config.ceiling.green);
	printf("C blue =\t%d\n", cub->config.ceiling.blue);
	printf("\n");
	printf("path north =\t{%s}\n", cub->config.path_n);
	printf("path south =\t{%s}\n", cub->config.path_s);
	printf("path west =\t{%s}\n", cub->config.path_w);
	printf("path east =\t{%s}\n", cub->config.path_e);
	printf("\n");
	printf("pos.x =\t\t%f\npos.y =\t\t%f\n\n", cub->pos.x, cub->pos.y);
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
			return (cub_error(E_MAP, STDERR_FILENO, cub));
		if ((int)ft_strlen(config[i]) > cub->config.map_w)
			cub->config.map_w = ft_strlen(config[i]);
		cub->config.map_h++;
	}
	if (cub->config.map_h < 3 || cub->config.map_w < 3)
		return (cub_error(E_MAP, STDERR_FILENO, cub));
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
<<<<<<< HEAD
	free(cub->textures.north);
	free(cub->textures.south);
	free(cub->textures.east);
	free(cub->textures.west);
=======
	free_errors(cub, cub->error.num);
>>>>>>> vheran
}
