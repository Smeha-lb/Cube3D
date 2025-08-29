#include "../includes/cub3d.h"

int	on_mouse_move(int x, int y, void *param)
{
	t_app *a;
	double dx;
	double cs;
	double sn;
	double old_dx;
	double old_px;

	(void)y;
	a = (t_app *)param;
	if (a->last_mouse_x < 0)
	{
		a->last_mouse_x = WIN_W / 2;
		return (0);
	}
	dx = (double)(x - (WIN_W / 2));
	if (dx != 0.0)
	{
		double rot;

		rot = dx * 0.0025;
		cs = cos(rot);
		sn = sin(rot);
		old_dx = a->player.dir_x;
		a->player.dir_x = a->player.dir_x * cs - a->player.dir_y * sn;
		a->player.dir_y = old_dx * sn + a->player.dir_y * cs;
		old_px = a->player.plane_x;
		a->player.plane_x = a->player.plane_x * cs - a->player.plane_y * sn;
		a->player.plane_y = old_px * sn + a->player.plane_y * cs;
	}
	mlx_mouse_move(a->mlx, a->win, WIN_W / 2, WIN_H / 2);
	a->last_mouse_x = WIN_W / 2;
	return (0);
}


