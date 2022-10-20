#include "../includes/cub3d.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	create_trgb(t_rgb rgb)
{
	int	t;

	t = 0;
	return (t << 24 | rgb.red << 16 | rgb.green << 8 | rgb.blue);
}
