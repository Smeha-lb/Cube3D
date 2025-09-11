/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:16:46 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/09 13:03:54 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MM_SCALE 6
#define MM_OX 10
#define MM_OY 10

static void	draw_cell_color(t_image *img, int x, int y, int c)
{
	int		i;
	int		j;
	int		off;
	char	*dst;

	i = 0;
	while (i < MM_SCALE)
	{
		j = 0;
		while (j < MM_SCALE)
		{
			off = (y + i) * img->line_len + (x + j) * (img->bpp / 8);
			dst = img->addr + off;
			*(unsigned int *)dst = (unsigned int)c;
			j++;
		}
		i++;
	}
}

static void	draw_map_cells(t_app *app)
{
	int		y;
	int		x;
	int		ox;
	int		oy;
	int		c;

	oy = MM_OY;
	ox = MM_OX;
	y = 0;
	while (y < app->cfg.map.height)
	{
		x = 0;
		while (app->cfg.map.grid[y][x])
		{
			c = COLOR_MINIMAP_EMPTY;
			if (app->cfg.map.grid[y][x] == '1')
				c = COLOR_MINIMAP_WALL;
			else if (app->cfg.map.grid[y][x] == 'D')
				c = COLOR_MINIMAP_DOOR;
			draw_cell_color(&app->frame, ox + x * MM_SCALE,
				oy + y * MM_SCALE, c);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_app *app)
{
	int	x;
	int	y;
	int	i;
	int	j;

	draw_map_cells(app);
	x = MM_OX + (int)(app->player.x * MM_SCALE) - 2;
	y = MM_OY + (int)(app->player.y * MM_SCALE) - 2;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			draw_cell_color(&app->frame, x + j, y + i, COLOR_MINIMAP_PLAYER);
			j++;
		}
		i++;
	}
}

static int	write_number(char *buf, int i, int v)
{
	if (v < 0)
		v = 0;
	if (v > 99)
		v = 99;
	if (v >= 10)
	{
		buf[i++] = '0' + (v / 10);
		buf[i++] = '0' + (v % 10);
		return (i);
	}
	buf[i++] = '0' + v;
	return (i);
}

void	draw_hud(t_app *app)
{
	char	buf[32];
	int		i;

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
	i = write_number(buf, i, app->torch_count);
	buf[i++] = '/';
	i = write_number(buf, i, app->total_torches);
	buf[i++] = ')';
	buf[i] = '\0';
	mlx_string_put(app->mlx, app->win, WIN_W - 180, WIN_H - 30, 0xFFFF00, buf);
}
