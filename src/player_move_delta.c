/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_delta.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:41:44 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 13:46:59 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

static long	now_ms(void)
{
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = (long)tv.tv_sec * 1000L + (long)(tv.tv_usec / 1000L);
	return (now);
}

void	update_time_and_speeds(t_app *app)
{
	long	now;
	long	dt_ms;
	double	dt;

	now = now_ms();
	dt_ms = now - app->last_time_ms;
	if (dt_ms < 0)
		dt_ms = 0;
	if (dt_ms > 100)
		dt_ms = 100;
	dt = (double)dt_ms / 800.0;
	app->last_time_ms = now;
	app->player.move_speed = app->base_move_speed * dt;
	app->player.rot_speed = app->base_rot_speed * dt;
}

void	add_forward(t_app *app, double *dx, double *dy, double s)
{
	*dx += app->player.dir_x * s;
	*dy += app->player.dir_y * s;
}

void	add_backward(t_app *app, double *dx, double *dy, double s)
{
	*dx -= app->player.dir_x * s;
	*dy -= app->player.dir_y * s;
}

void	add_left(t_app *app, double *dx, double *dy, double s)
{
	*dx -= app->player.plane_x * s;
	*dy -= app->player.plane_y * s;
}
