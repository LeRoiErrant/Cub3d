#include "../includes/cub3d.h"

void	anim_door(t_cub3d *cub)
{
	cub->framecount++;
	if (cub->framecount % 8 == 0)
	{
		if (cub->door_side < TEX_SIDE4 && !cub->appear)
			cub->door_side++;
		else if (cub->door_side == TEX_SIDE4 && !cub->appear)
			cub->appear = 1;
		else if (cub->door_side > TEX_SIDE0 && cub->appear)
			cub->door_side--;
		else if (cub->door_side == TEX_SIDE0 && cub->appear)
		{
			cub->framecount = 0;
			cub->appear = 0;
		}
	}
}

void	animation(t_cub3d *cub)
{
	anim_door(cub);
	if (cub->shoot)
	{
		cub->g_framecount++;
		if (cub->g_framecount % 8 == 0)
		{
			if (cub->gun_frame == TEX_GUN5)
			{
				cub->gun_frame = TEX_GUN0;
				cub->shoot = 0;
				cub->g_framecount = 0;
			}
			else if (cub->gun_frame < TEX_GUN5)
				cub->gun_frame++;
		}
	}
}