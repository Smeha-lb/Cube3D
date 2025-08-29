#include "../includes/cub3d.h"

static void	set_dir_plane(t_player *p, char d)
{
	if (d == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (d == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (d == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	init_player_from_map(t_app *app)
{
	t_map *m;

	m = &app->cfg.map;
	app->player.x = m->player_x + 0.5;
	app->player.y = m->player_y + 0.5;
	set_dir_plane(&app->player, m->player_dir);
	app->player.move_speed = 0.02;
	app->player.rot_speed = 0.025;
}

static void	try_move(t_app *app, double nx, double ny)
{
	double off;
	double cx;
	double cy;

	off = 0.15;
	cx = nx;
	if (nx > app->player.x)
		cx = nx + off;
	else
		cx = nx - off;
	cy = app->player.y;
	if (!map_is_wall(&app->cfg.map, (int)cx, (int)cy))
		app->player.x = nx;
	cx = app->player.x;
	cy = ny;
	if (ny > app->player.y)
		cy = ny + off;
	else
		cy = ny - off;
	if (!map_is_wall(&app->cfg.map, (int)cx, (int)cy))
		app->player.y = ny;
}

static void	build_move_delta(t_app *app, double *dx, double *dy)
{
	double s;
	double len;

	*dx = 0.0;
	*dy = 0.0;
	s = app->player.move_speed;
	if (app->keys.w)
	{
		*dx += app->player.dir_x * s;
		*dy += app->player.dir_y * s;
	}
	if (app->keys.s)
	{
		*dx -= app->player.dir_x * s;
		*dy -= app->player.dir_y * s;
	}
	if (app->keys.a)
	{
		*dx -= app->player.plane_x * s;
		*dy -= app->player.plane_y * s;
	}
	if (app->keys.d)
	{
		*dx += app->player.plane_x * s;
		*dy += app->player.plane_y * s;
	}
	len = sqrt((*dx) * (*dx) + (*dy) * (*dy));
	if (len > s && len > 0.0)
	{
		*dx = *dx / len * s;
		*dy = *dy / len * s;
	}
}

void	update_player(t_app *app)
{
	double cs;
	double sn;
	double old_dx;
	double old_px;
	double dx;
	double dy;

	build_move_delta(app, &dx, &dy);
	if (dx != 0.0 || dy != 0.0)
		try_move(app, app->player.x + dx, app->player.y + dy);
	if (app->keys.left || app->keys.right)
	{
		if (app->keys.right)
		{
			cs = cos(app->player.rot_speed);
			sn = sin(app->player.rot_speed);
		}
		else
		{
			cs = cos(-app->player.rot_speed);
			sn = sin(-app->player.rot_speed);
		}
		old_dx = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cs - app->player.dir_y * sn;
		app->player.dir_y = old_dx * sn + app->player.dir_y * cs;
		old_px = app->player.plane_x;
		app->player.plane_x = app->player.plane_x * cs - app->player.plane_y * sn;
		app->player.plane_y = old_px * sn + app->player.plane_y * cs;
	}
}


