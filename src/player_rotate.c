/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:29:39 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:29:48 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	apply_rotation_from_keys(t_app *app)
{
	double	cs;
	double	sn;
	double	a;
	double	old_dx;
	double	old_px;

	if (!app->keys.left && !app->keys.right)
		return ;
	a = app->player.rot_speed;
	if (app->keys.left)
		a = -a;
	cs = cos(a);
	sn = sin(a);
	old_dx = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cs - app->player.dir_y * sn;
	app->player.dir_y = old_dx * sn + app->player.dir_y * cs;
	old_px = app->player.plane_x;
	app->player.plane_x = app->player.plane_x * cs - app->player.plane_y * sn;
	app->player.plane_y = old_px * sn + app->player.plane_y * cs;
}
