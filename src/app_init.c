/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:21:51 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/11 14:42:56 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	load_map_and_window(t_app *app, const char *map_path)
{
	if (parse_cub_file(map_path, &app->cfg))
		return (free_config(&app->cfg), 1);
	if (setup_mlx_and_window(app))
		return (1);
	if (setup_frame(app))
		return (1);
	return (0);
}

static void	init_gameplay_defaults(t_app *app)
{
	app->running = 1;
	app->torch_count = 0;
	app->hud_msg_timer = 0;
	app->total_torches = app->cfg.num_sprites;
	app->base_move_speed = 2.5;
	app->base_rot_speed = 1.5;
}

static int	load_assets_and_sprites(t_app *app)
{
	if (load_textures(app->mlx, &app->cfg))
		return (1);
	if (init_sprites(&app->cfg))
		return (1);
	return (0);
}

int	app_init(t_app *app, const char *map_path)
{
	if (!app)
		return (1);
	zero_config(&app->cfg);
	zero_keys(&app->keys);
	app->last_mouse_x = -1;
	if (load_map_and_window(app, map_path))
		return (1);
	if (load_assets_and_sprites(app))
		return (1);
	init_player_from_map(app);
	init_gameplay_defaults(app);
	init_time_now(app);
	setup_animation_defaults(app);
	setup_hooks(app);
	return (0);
}
