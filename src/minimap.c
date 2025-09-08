/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:16:46 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/08 14:16:47 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_px(t_image *img, int x, int y, int c)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)c;
}

static void	draw_rect(t_image *img, int x, int y, int w, int h, int c)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			put_px(img, x + j, y + i, c);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_app *app)
{
	int scale;
	int y;
	int x;
	int ox;
	int oy;

	scale = 6;
	oy = 10;
	ox = 10;
	y = 0;
	while (y < app->cfg.map.height)
	{
		x = 0;
		while (app->cfg.map.grid[y][x])
		{
			if (app->cfg.map.grid[y][x] == '1')
				draw_rect(&app->frame, ox + x * scale, oy + y * scale, scale, scale, COLOR_MINIMAP_WALL);
			else if (app->cfg.map.grid[y][x] == 'D')
				draw_rect(&app->frame, ox + x * scale, oy + y * scale, scale, scale, COLOR_MINIMAP_DOOR);
			else
				draw_rect(&app->frame, ox + x * scale, oy + y * scale, scale, scale, COLOR_MINIMAP_EMPTY);
			x++;
		}
		y++;
	}
	draw_rect(&app->frame,
			 ox + (int)(app->player.x * scale) - 2,
			 oy + (int)(app->player.y * scale) - 2,
			 4, 4, COLOR_MINIMAP_PLAYER);
}

void	draw_hud(t_app *app)
{
	char	buf[64];
	int		x;
	int		y;
	int		a;
	int		b;
	int		i;

	x = WIN_W - 180;
	y = WIN_H - 90;
	i = 0;
	buf[i++] = 'T';
	buf[i++] = 'o';
	buf[i++] = 'r';
	buf[i++] = 'c';
	buf[i++] = 'h';
	buf[i++] = 'e';
	buf[i++] = 's';
	buf[i++] = ' ';
	buf[i++] = '(';
	a = app->torch_count;
	if (a < 0)
		a = 0;
	if (a > 99)
		a = 99;
	if (a >= 10)
	{
		buf[i++] = '0' + (a / 10);
		buf[i++] = '0' + (a % 10);
	}
	else
		buf[i++] = '0' + a;
	buf[i++] = '/';
	b = app->total_torches;
	if (b < 0)
		b = 0;
	if (b > 99)
		b = 99;
	if (b >= 10)
	{
		buf[i++] = '0' + (b / 10);
		buf[i++] = '0' + (b % 10);
	}
	else
		buf[i++] = '0' + b;
	buf[i++] = ')';
	buf[i] = '\0';
	mlx_string_put(app->mlx, app->win, x, y, 0xFFFF00, buf);
}
