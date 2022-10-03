#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc != 2)
		return (cub_error(E_ARGC, STDERR_FILENO));
	init_cub(&cub);
	if (parsing(argv, &cub) != SUCCESS)
		return (cub_error(E_FAILURE, -1));
	mlx_test(&cub);
	free_cub(&cub);
	return (cub.errnum);
}
