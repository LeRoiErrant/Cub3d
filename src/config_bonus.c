#include "../includes/cub3d.h"

static int	config_opn_door(t_cub3d *cub)
{
	cub->config.path[TEX_OPN0] = ft_strdup("./assets/vheran/42/nopen00.xpm");
	if (check_path(cub->config.path[TEX_OPN0]))
		return (E_PATH);
	cub->config.path[TEX_OPN1] = ft_strdup("./assets/vheran/42/nopen01.xpm");
	if (check_path(cub->config.path[TEX_OPN1]))
		return (E_PATH);
	cub->config.path[TEX_OPN2] = ft_strdup("./assets/vheran/42/nopen02.xpm");
	if (check_path(cub->config.path[TEX_OPN2]))
		return (E_PATH);
	cub->config.path[TEX_OPN3] = ft_strdup("./assets/vheran/42/nopen03.xpm");
	if (check_path(cub->config.path[TEX_OPN3]))
		return (E_PATH);
	cub->config.path[TEX_OPN4] = ft_strdup("./assets/vheran/42/nopen04.xpm");
	if (check_path(cub->config.path[TEX_OPN4]))
		return (E_PATH);
	return (SUCCESS);
}

int	config_doors(t_cub3d *cub)
{
	cub->config.path[TEX_CLS] = ft_strdup("./assets/vheran/42/closed.xpm");
	if (check_path(cub->config.path[TEX_CLS]))
		return (E_PATH);
	if (config_opn_door(cub))
		return (E_PATH);
	cub->config.path[TEX_SIDE0] = ft_strdup("./assets/vheran/42/door00.xpm");
	if (check_path(cub->config.path[TEX_SIDE0]))
		return (E_PATH);
	cub->config.path[TEX_SIDE1] = ft_strdup("./assets/vheran/42/door01.xpm");
	if (check_path(cub->config.path[TEX_SIDE1]))
		return (E_PATH);
	cub->config.path[TEX_SIDE2] = ft_strdup("./assets/vheran/42/door02.xpm");
	if (check_path(cub->config.path[TEX_SIDE2]))
		return (E_PATH);
	cub->config.path[TEX_SIDE3] = ft_strdup("./assets/vheran/42/door03.xpm");
	if (check_path(cub->config.path[TEX_SIDE3]))
		return (E_PATH);
	cub->config.path[TEX_SIDE4] = ft_strdup("./assets/vheran/42/door04.xpm");
	if (check_path(cub->config.path[TEX_SIDE4]))
		return (E_PATH);
	return (SUCCESS);
}

int	config_guns(t_cub3d *cub)
{
	cub->config.path[TEX_GUN0] = ft_strdup("./assets/vheran/Gun/gun00.xpm");
	if (check_path(cub->config.path[TEX_GUN0]))
		return (E_PATH);
	cub->config.path[TEX_GUN1] = ft_strdup("./assets/vheran/Gun/gun01.xpm");
	if (check_path(cub->config.path[TEX_GUN1]))
		return (E_PATH);
	cub->config.path[TEX_GUN2] = ft_strdup("./assets/vheran/Gun/gun02.xpm");
	if (check_path(cub->config.path[TEX_GUN2]))
		return (E_PATH);
	cub->config.path[TEX_GUN3] = ft_strdup("./assets/vheran/Gun/gun03.xpm");
	if (check_path(cub->config.path[TEX_GUN3]))
		return (E_PATH);
	cub->config.path[TEX_GUN4] = ft_strdup("./assets/vheran/Gun/gun04.xpm");
	if (check_path(cub->config.path[TEX_GUN4]))
		return (E_PATH);
	cub->config.path[TEX_GUN5] = ft_strdup("./assets/vheran/Gun/gun05.xpm");
	if (check_path(cub->config.path[TEX_GUN5]))
		return (E_PATH);
	return (SUCCESS);
}
