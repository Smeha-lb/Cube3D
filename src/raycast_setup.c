/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:40:02 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 13:47:08 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_deltas(t_ray *r)
{
	if (r->rdx == 0.0)
		r->ddx = 1e30;
	else
		r->ddx = fabs(1.0 / r->rdx);
	if (r->rdy == 0.0)
		r->ddy = 1e30;
	else
		r->ddy = fabs(1.0 / r->rdy);
}

static void	set_steps(t_app *app, t_ray *r)
{
	if (r->rdx < 0)
	{
		r->step_x = -1;
		r->sdx = (app->player.x - r->map_x) * r->ddx;
	}
	else
	{
		r->step_x = 1;
		r->sdx = (r->map_x + 1.0 - app->player.x) * r->ddx;
	}
	if (r->rdy < 0)
	{
		r->step_y = -1;
		r->sdy = (app->player.y - r->map_y) * r->ddy;
	}
	else
	{
		r->step_y = 1;
		r->sdy = (r->map_y + 1.0 - app->player.y) * r->ddy;
	}
}

void	setup_ray(t_app *app, t_ray *r)
{
	r->cam_x = 2.0 * r->x / (double)WIN_W - 1.0;
	r->rdx = app->player.dir_x + app->player.plane_x * r->cam_x;
	r->rdy = app->player.dir_y + app->player.plane_y * r->cam_x;
	r->map_x = (int)app->player.x;
	r->map_y = (int)app->player.y;
	set_deltas(r);
	set_steps(app, r);
	r->hit = 0;
}
