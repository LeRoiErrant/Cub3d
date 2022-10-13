#include "../includes/cub3d.h"

void	init_engine(t_cub3d *cub)
{
	cub->engine.move.up = 0;
	cub->engine.move.left = 0;
	cub->engine.move.down = 0;
	cub->engine.move.right = 0;
	cub->engine.rot.left = 0;
	cub->engine.rot.right = 0;
	cub->engine.delta.x = 0;
	cub->engine.delta.y = 0;
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub;

	if (argc != 2)
		return (cub_error(E_ARGC, STDERR_FILENO));
	cub = ft_calloc(1, sizeof(t_cub3d));
	if (!cub)
		return(cub_error(E_MALLOC, -1));
	init_cub(cub);
	if (parsing(argv, cub) != SUCCESS)
		return (cub_error_free(E_FAILURE, -1, cub));
	init_engine(cub);
	loop(cub);
	free_cub(cub);
	return (cub->errnum);
}
