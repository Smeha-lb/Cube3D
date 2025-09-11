/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:52 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/11 13:40:36 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_tex_color(t_texture *tx, int x, int y)
{
	char	*p;

	if (x < 0)
		x = 0;
	if (x >= tx->w)
		x = tx->w - 1;
	if (y < 0)
		y = 0;
	if (y >= tx->h)
		y = tx->h - 1;
	p = tx->addr + y * tx->line_len + x * (tx->bpp / 8);
	return (*(int *)p);
}

t_texture	*pick_side(t_app *app, int side
		, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (&app->cfg.tex_we);
		return (&app->cfg.tex_ea);
	}
	if (ray_dir_y > 0)
		return (&app->cfg.tex_no);
	return (&app->cfg.tex_so);
}

/* setup_ray moved to raycast_setup.c to satisfy line limits */

void	walk_until_hit(t_app *app, t_ray *r)
{
	while (!r->hit)
	{
		if (r->sdx < r->sdy)
		{
			r->sdx += r->ddx;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->sdy += r->ddy;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map_is_wall(&app->cfg.map, r->map_x, r->map_y))
			r->hit = 1;
		else if (app->cfg.map.grid[r->map_y][r->map_x] == 'D')
			r->hit = 1;
	}
}

void	compute_column_params(t_app *app, t_ray *r)
{
	if (r->side == 0)
		r->pwd = (r->map_x - app->player.x + (1 - r->step_x) / 2.0) / r->rdx;
	else
		r->pwd = (r->map_y - app->player.y + (1 - r->step_y) / 2.0) / r->rdy;
	r->line_h = (int)(WIN_H / r->pwd);
	r->draw_s = -r->line_h / 2 + WIN_H / 2;
	if (r->draw_s < 0)
		r->draw_s = 0;
	r->draw_e = r->line_h / 2 + WIN_H / 2;
	if (r->draw_e >= WIN_H)
		r->draw_e = WIN_H - 1;
	if (r->side == 0)
		r->wall_x = app->player.y + r->pwd * r->rdy;
	else
		r->wall_x = app->player.x + r->pwd * r->rdx;
	r->wall_x -= floor(r->wall_x);
	if (r->wall_x < 1e-6)
		r->wall_x = 1e-6;
	else if (r->wall_x > 1.0 - 1e-6)
		r->wall_x = 1.0 - 1e-6;
}
