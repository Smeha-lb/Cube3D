/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:02:10 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 15:05:59 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	clamp_local(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

int	get_sprite_color(t_texture *tx, int x, int y)
{
	char	*p;

	x = clamp_local(x, 0, tx->w - 1);
	y = clamp_local(y, 0, tx->h - 1);
	p = tx->addr + y * tx->line_len + x * (tx->bpp / 8);
	return (*(int *)p);
}

t_texture	*choose_torch_texture(t_app *app)
{
	if (app->cfg.torch_frame_count > 0)
		return (&app->cfg.torch_frames[
				app->torch_frame_index % app->cfg.torch_frame_count]);
	return (&app->cfg.tex_torch);
}

void	store_sprite_pixel(t_app *app, int x, int y, int color)
{
	char	*dst;

	dst = app->frame.addr
		+ (y * app->frame.line_len + x * (app->frame.bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}
