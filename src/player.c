/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:11:42 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/08 14:13:41 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

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
	t_map	*m;

	m = &app->cfg.map;
	app->player.x = m->player_x + 0.5;
	app->player.y = m->player_y + 0.5;
	set_dir_plane(&app->player, m->player_dir);
	app->player.move_speed = 0.0;
	app->player.rot_speed = 0.0;
}

static int	is_wall_cell(t_map *m, double x, double y)
{
	int	gx;
	int	gy;

	gx = (int)floor(x);
	gy = (int)floor(y);
	if (map_is_wall(m, gx, gy))
		return (1);
	return (0);
}

static void	try_move(t_app *app, double nx, double ny)
{
	double	r;
	double	y;
	double	x;
	double	sx;
	double	sy;

	r = 0.20;
	y = app->player.y;
	sx = r;
	if (nx < app->player.x)
		sx = -r;
	if (!is_wall_cell(&app->cfg.map, nx + sx, y)
		&& !is_wall_cell(&app->cfg.map, nx + sx, y + r)
		&& !is_wall_cell(&app->cfg.map, nx + sx, y - r))
		app->player.x = nx;
	x = app->player.x;
	sy = r;
	if (ny < app->player.y)
		sy = -r;
	if (!is_wall_cell(&app->cfg.map, x, ny + sy)
		&& !is_wall_cell(&app->cfg.map, x + r, ny + sy)
		&& !is_wall_cell(&app->cfg.map, x - r, ny + sy))
		app->player.y = ny;
}

static void	build_move_delta(t_app *app, double *dx, double *dy)
{
	double			s;
	struct timeval	tv;
	long			now;
	long			dt_ms;
	double			dt;
	double			len;

	gettimeofday(&tv, NULL);
	now = (long)tv.tv_sec * 1000L + (long)(tv.tv_usec / 1000L);
	dt_ms = now - app->last_time_ms;
	if (dt_ms < 0)
		dt_ms = 0;
	if (dt_ms > 100)
		dt_ms = 100;
	dt = (double)dt_ms / 1000.0;
	app->last_time_ms = now;
	app->player.move_speed = app->base_move_speed * dt;
	app->player.rot_speed = app->base_rot_speed * dt;
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
	double	cs;
	double	sn;
	double	old_dx;
	double	old_px;
	double	dx;
	double	dy;

	build_move_delta(app, &dx, &dy);
	if (dx != 0.0 || dy != 0.0)
	{
		try_move(app, app->player.x + dx, app->player.y + dy);
		pickup_sprites_near_player(app);
	}
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
