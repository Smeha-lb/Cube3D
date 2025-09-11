/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:26:04 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 13:38:34 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	zero_config(t_config *cfg)
{
	cfg->tex_no.path = NULL;
	cfg->tex_so.path = NULL;
	cfg->tex_we.path = NULL;
	cfg->tex_ea.path = NULL;
	cfg->tex_no.img = NULL;
	cfg->tex_so.img = NULL;
	cfg->tex_we.img = NULL;
	cfg->tex_ea.img = NULL;
	cfg->tex_door.path = NULL;
	cfg->tex_door.img = NULL;
	cfg->tex_torch.path = NULL;
	cfg->tex_torch.img = NULL;
	cfg->map.grid = NULL;
	cfg->sprites = NULL;
	cfg->num_sprites = 0;
}

void	zero_keys(t_keys *k)
{
	k->w = 0;
	k->a = 0;
	k->s = 0;
	k->d = 0;
	k->left = 0;
	k->right = 0;
}

void	center_mouse(t_app *app)
{
	mlx_mouse_move(app->mlx, app->win, WIN_W / 2, WIN_H / 2);
	app->last_mouse_x = WIN_W / 2;
}

int	setup_mlx_and_window(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (1);
	app->win = mlx_new_window(app->mlx, WIN_W, WIN_H, "cub3D");
	if (!app->win)
		return (1);
	mlx_mouse_hide(app->mlx, app->win);
	center_mouse(app);
	return (0);
}

void	setup_animation_defaults(t_app *app)
{
	app->torch_frame_index = 0;
	app->torch_frame_ms = TORCH_FRAME_MS;
	app->torch_anim_accum_ms = 0;
	app->last_anim_time_ms = app->last_time_ms;
}
