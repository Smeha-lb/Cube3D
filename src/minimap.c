#include "../includes/cub3d.h"

static void	put_px(t_image *img, int x, int y, int c)
{
	char *dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)c;
}

static void	draw_rect(t_image *img, int x, int y, int w, int h, int c)
{
	int i;
	int j;

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
	(void)app;
}


