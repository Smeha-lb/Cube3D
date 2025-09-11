/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:38:28 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:38:34 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_player(t_app *app)
{
	double	dx;
	double	dy;

	compute_move_delta(app, &dx, &dy);
	if (dx != 0.0 || dy != 0.0)
	{
		try_move_player(app, app->player.x + dx, app->player.y + dy);
		pickup_sprites_near_player(app);
	}
	apply_rotation_from_keys(app);
}
