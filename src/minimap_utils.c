#include "../includes/cub3d.h"

void	get_start(t_cub3d *cub, t_ipos *start)
{
	start->x = (int) cub->pos.x - 5;
	start->y = (int) cub->pos.y - 5;
}

int	get_map_color(t_cub3d *cub, int x, int y)
{
	(void) cub;
	(void) x;
	(void) y;
	if (cub->map[x][y] == '1')
		return (HEX_DARK_RED);
	else if (cub->map[x][y] == 'D')
		return (HEX_DARK_BLUE);
	else if (cub->map[x][y] != '.')
		return (0x00AAAAAA);
	else
		return (0x00000000);
	return (HEX_RED);
}

int	is_in_map(t_cub3d *cub, t_ipos start, t_ipos cell)
{
	if (start.x + cell.x < 0 || start.x + cell.x >= cub->config.map_h)
		return (0);
	else if (start.y + cell.y < 0 || start.y + cell.y >= cub->config.map_w)
		return (0);
	else
		return (1);
}
