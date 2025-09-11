/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_try.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:08 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:30:31 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static void	try_move_x(t_app *app, double nx, double r)
{
	double	y;
	double	sx;

	y = app->player.y;
	sx = r;
	if (nx < app->player.x)
		sx = -r;
	if (!is_wall_cell(&app->cfg.map, nx + sx, y)
		&& !is_wall_cell(&app->cfg.map, nx + sx, y + r)
		&& !is_wall_cell(&app->cfg.map, nx + sx, y - r))
		app->player.x = nx;
}

static void	try_move_y(t_app *app, double ny, double r)
{
	double	x;
	double	sy;

	x = app->player.x;
	sy = r;
	if (ny < app->player.y)
		sy = -r;
	if (!is_wall_cell(&app->cfg.map, x, ny + sy)
		&& !is_wall_cell(&app->cfg.map, x + r, ny + sy)
		&& !is_wall_cell(&app->cfg.map, x - r, ny + sy))
		app->player.y = ny;
}

void	try_move_player(t_app *app, double nx, double ny)
{
	double	r;

	r = 0.20;
	try_move_x(app, nx, r);
	try_move_y(app, ny, r);
}
