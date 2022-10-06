#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	init_errors(&cub);
	if (argc != 2)
		return (cub_error(E_ARGC, STDERR_FILENO, &cub));
	init_cub(&cub);
	if (parsing(argv, &cub) != SUCCESS)
		return (cub_error_free(E_FAILURE, -1, &cub));
	loop(&cub);
	free_cub(&cub);
	return (cub.error.num);
}
