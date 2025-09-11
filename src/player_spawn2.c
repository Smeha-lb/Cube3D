/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:46 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:31:41 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
