/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:09:46 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/11 15:31:37 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* helpers moved to sprites_utils.c */

static int	compute_sprite_transform(t_app *app, t_sprite *s,
	t_sprite_stripes *out)
{
	double	inv;
	double	tr_x;
	double	tr_y;

	inv = 1.0 / (app->player.plane_x * app->player.dir_y
			- app->player.dir_x * app->player.plane_y);
	tr_x = inv * (app->player.dir_y * (s->x - app->player.x)
			- app->player.dir_x * (s->y - app->player.y));
	tr_y = inv * (-app->player.plane_y * (s->x - app->player.x)
			+ app->player.plane_x * (s->y - app->player.y));
	if (tr_y <= 0)
		return (1);
	out->x = (int)((WIN_W / 2.0) * (1.0 + tr_x / tr_y));
	out->sw = (int)fabs((double)(WIN_H / tr_y));
	out->dy0 = -out->sw / 2 + WIN_H / 2;
	if (out->dy0 < 0)
		out->dy0 = 0;
	out->dy1 = out->sw / 2 + WIN_H / 2;
	if (out->dy1 >= WIN_H)
		out->dy1 = WIN_H - 1;
	out->depth = tr_y;
	return (0);
}

static void	compute_sprite_sampling(t_app *app, t_sprite_stripes *out)
{
	t_texture	*t;

	t = choose_torch_texture(app);
	out->tx_step = (double)t->h / (double)out->sw;
	out->tpos_start = (out->dy0 - (-out->sw / 2.0 + WIN_H / 2.0))
		* out->tx_step + 0.5;
	out->tex_w = t->w;
}

int	compute_sprite_stripes(t_app *app, t_sprite *s, t_sprite_stripes *out)
{
	if (compute_sprite_transform(app, s, out) != 0)
		return (1);
	compute_sprite_sampling(app, out);
	return (0);
}

static void	blit_sprite_column(t_app *app, t_sprite_col c,
	double step, double tpos_start)
{
	int			y;
	double		tpos;
	int			color;
	t_texture	*tx_img;

	tx_img = choose_torch_texture(app);
	tpos = tpos_start;
	y = c.y0;
	while (y < c.y1)
	{
		color = get_sprite_color(tx_img, c.tex_x, (int)tpos);
		if ((color & 0x00FFFFFF) != 0)
			store_sprite_pixel(app, c.x, y, color);
		tpos += step;
		y++;
	}
}

void	render_sprite_stripes(t_app *app, t_sprite_stripes s)
{
	int			stripe;
	int			tx;
	double		z;

	stripe = s.x - (int)(s.sw / 2.0);
	if (stripe < 0)
		stripe = 0;
	while (stripe < s.x + (int)(s.sw / 2.0) && stripe < WIN_W)
	{
		z = app->zbuf[stripe];
		if (z <= 0.0 || s.depth < z)
		{
			tx = (int)((stripe - (s.x - (int)(s.sw / 2.0)))
					* s.tex_w / (double)s.sw);
			blit_sprite_column(app,
				(t_sprite_col){stripe, s.dy0,
				s.dy1, tx}, s.tx_step,
				s.tpos_start);
		}
		stripe++;
	}
}
