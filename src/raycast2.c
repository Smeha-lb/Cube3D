/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:52 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/11 13:18:01 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	prepare_texture(t_app *app, t_ray *r)
{
	if (app->cfg.map.grid[r->map_y][r->map_x] == 'D' && app->cfg.tex_door.img)
		r->tx = &app->cfg.tex_door;
	else
		r->tx = pick_side(app, r->side, r->rdx, r->rdy);
	r->tex_x = (int)(r->wall_x * (double)r->tx->w);
	if ((r->side == 0 && r->rdx > 0) || (r->side == 1 && r->rdy < 0))
		r->tex_x = r->tx->w - r->tex_x - 1;
	if (r->tex_x < 0)
		r->tex_x = 0;
	else if (r->tex_x >= r->tx->w)
		r->tex_x = r->tx->w - 1;
	r->step = 1.0 * r->tx->h / r->line_h;
	r->tex_pos = (r->draw_s - WIN_H / 2.0 + r->line_h / 2.0) * r->step;
	r->tex_pos += 0.5;
}

void	render_column(t_app *app, t_ray *r)
{
	char	*dst;

	r->y = r->draw_s;
	while (r->y < r->draw_e)
	{
		if (r->tex_pos < 0.0)
			r->tex_y = 0;
		else if ((int)r->tex_pos >= r->tx->h)
			r->tex_y = r->tx->h - 1;
		else
			r->tex_y = (int)r->tex_pos;
		r->tex_pos += r->step;
		r->color = get_tex_color(r->tx, r->tex_x, r->tex_y);
		dst = app->frame.addr
			+ (r->y * app->frame.line_len + r->x * (app->frame.bpp / 8));
		*(unsigned int *)dst = (unsigned int)r->color;
		r->y++;
	}
	app->zbuf[r->x] = r->pwd;
}

void	raycast_frame(t_app *app)
{
	t_ray	r;

	r.x = 0;
	while (r.x < WIN_W)
	{
		setup_ray(app, &r);
		walk_until_hit(app, &r);
		compute_column_params(app, &r);
		prepare_texture(app, &r);
		render_column(app, &r);
		r.x++;
	}
}
