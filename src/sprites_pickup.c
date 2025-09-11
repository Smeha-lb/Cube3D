/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_pickup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:02:24 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:18:49 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	sprite_is_close(t_app *app, t_sprite *s)
{
	double	dx;
	double	dy;
	double	d2;

	dx = s->x - app->player.x;
	dy = s->y - app->player.y;
	d2 = dx * dx + dy * dy;
	if (d2 < 0.25)
		return (1);
	return (0);
}

static void	remove_sprite_at_index(t_config *cfg, int idx)
{
	int	i;

	i = idx;
	while (i + 1 < cfg->num_sprites)
	{
		cfg->sprites[i] = cfg->sprites[i + 1];
		i++;
	}
	cfg->num_sprites--;
}

void	pickup_sprites_near_player(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->cfg.num_sprites)
	{
		if (sprite_is_close(app, &app->cfg.sprites[i]))
		{
			remove_sprite_at_index(&app->cfg, i);
			app->torch_count = app->torch_count + 1;
			app->hud_msg_timer = 120;
			continue ;
		}
		i++;
	}
}
