#include "../includes/cub3d.h"

static void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_half(t_image *img, int y0, int y1, int color)
{
	int	y;
	int	x;

	y = y0;
	while (y < y1)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_background(t_image *img, int ceil_color, int floor_color)
{
	draw_half(img, 0, WIN_H / 2, ceil_color);
	draw_half(img, WIN_H / 2, WIN_H, floor_color);
}

int	render_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app->running)
		return (0);
	update_player(app);
	draw_background(&app->frame, app->cfg.ceiling.argb, app->cfg.floor.argb);
	raycast_frame(app);
	draw_sprites(app);
	draw_minimap(app);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.handle, 0, 0);
	draw_hud(app);
	return (0);
}
