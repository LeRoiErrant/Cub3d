/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:44:58 by 0xNino            #+#    #+#             */
/*   Updated: 2022/11/02 10:44:59 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub;

	if (argc != 2)
		return (cub_error(E_ARGC, STDERR_FILENO));
	if (check_extension(argv[1]))
		return (cub_error(E_EXT, STDERR_FILENO));
	cub = ft_calloc(1, sizeof(t_cub3d));
	if (!cub)
		return (cub_error(E_MALLOC, -1));
	init_cub(cub);
	if (parsing(argv, cub) != SUCCESS)
		return (cub_error_free(E_FAILURE, -1, cub));
	game(cub);
	free_cub(cub);
	return (cub->errnum);
}
