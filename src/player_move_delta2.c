/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_delta2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:43:29 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 13:46:52 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

void	add_right(t_app *app, double *dx, double *dy, double s)
{
	*dx += app->player.plane_x * s;
	*dy += app->player.plane_y * s;
}

void	limit_by_len(double *dx, double *dy, double s)
{
	double	len;

	len = sqrt((*dx) * (*dx) + (*dy) * (*dy));
	if (len > s && len > 0.0)
	{
		*dx = *dx / len * s;
		*dy = *dy / len * s;
	}
}

int	compute_move_delta(t_app *app, double *dx, double *dy)
{
	double	s;

	update_time_and_speeds(app);
	*dx = 0.0;
	*dy = 0.0;
	s = app->player.move_speed;
	if (app->keys.w)
		add_forward(app, dx, dy, s);
	if (app->keys.s)
		add_backward(app, dx, dy, s);
	if (app->keys.a)
		add_left(app, dx, dy, s);
	if (app->keys.d)
		add_right(app, dx, dy, s);
	limit_by_len(dx, dy, s);
	return (0);
}
