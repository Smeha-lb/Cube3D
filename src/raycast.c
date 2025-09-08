/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:52 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/08 14:11:05 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_tex_color(t_texture *tx, int x, int y)
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

static t_texture	*pick_side(t_app *app, int side, double ray_dir_x, double ray_dir_y)
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

void	raycast_frame(t_app *app)
{
	int x;

	x = 0;
	while (x < WIN_W)
	{
		double camX;
		double rdx;
		double rdy;
		int mapX;
		int mapY;
		double sdx;
		double sdy;
		double ddx;
		double ddy;
		int stepX;
		int stepY;
		int hit;
		int side;
		double pwd;
		int line_h;
		int draw_s;
		int draw_e;
		double wallX;
		t_texture *tx;
		int tex_x;
		double step;
		double texPos;
		int y;
		int tex_y;
		int color;

		camX = 2.0 * x / (double)WIN_W - 1.0;
		rdx = app->player.dir_x + app->player.plane_x * camX;
		rdy = app->player.dir_y + app->player.plane_y * camX;
		mapX = (int)app->player.x;
		mapY = (int)app->player.y;
		ddx = (rdx == 0) ? 1e30 : fabs(1.0 / rdx);
		ddy = (rdy == 0) ? 1e30 : fabs(1.0 / rdy);
		if (rdx < 0)
		{
			stepX = -1;
			sdx = (app->player.x - mapX) * ddx;
		}
		else
		{
			stepX = 1;
			sdx = (mapX + 1.0 - app->player.x) * ddx;
		}
		if (rdy < 0)
		{
			stepY = -1;
			sdy = (app->player.y - mapY) * ddy;
		}
		else
		{
			stepY = 1;
			sdy = (mapY + 1.0 - app->player.y) * ddy;
		}
		hit = 0;
		while (!hit)
		{
			if (sdx < sdy)
			{
				sdx += ddx;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sdy += ddy;
				mapY += stepY;
				side = 1;
			}
			if (map_is_wall(&app->cfg.map, mapX, mapY))
				hit = 1;
			else if (app->cfg.map.grid[mapY][mapX] == 'D')
				hit = 1;
		}
		if (side == 0)
			pwd = (mapX - app->player.x + (1 - stepX) / 2.0) / rdx;
		else
			pwd = (mapY - app->player.y + (1 - stepY) / 2.0) / rdy;
		line_h = (int)(WIN_H / pwd);
		draw_s = -line_h / 2 + WIN_H / 2;
		if (draw_s < 0)
			draw_s = 0;
		draw_e = line_h / 2 + WIN_H / 2;
		if (draw_e >= WIN_H)
			draw_e = WIN_H - 1;
		if (side == 0)
			wallX = app->player.y + pwd * rdy;
		else
			wallX = app->player.x + pwd * rdx;
		wallX -= floor(wallX);
		if (app->cfg.map.grid[mapY][mapX] == 'D' && app->cfg.tex_door.img)
			tx = &app->cfg.tex_door;
		else
			tx = pick_side(app, side, rdx, rdy);
		tex_x = (int)(wallX * (double)tx->w);
		if ((side == 0 && rdx > 0) || (side == 1 && rdy < 0))
			tex_x = tx->w - tex_x - 1;
		step = 1.0 * tx->h / line_h;
		texPos = (draw_s - WIN_H / 2.0 + line_h / 2.0) * step;
		y = draw_s;
		while (y < draw_e)
		{
			tex_y = (int)texPos & (tx->h - 1);
			texPos += step;
			color = get_tex_color(tx, tex_x, tex_y);
			{
				char *dst;
				dst = app->frame.addr + (y * app->frame.line_len + x * (app->frame.bpp / 8));
				*(unsigned int *)dst = (unsigned int)color;
			}
			y++;
		}
		app->zbuf[x] = pwd;
		x++;
	}
}
