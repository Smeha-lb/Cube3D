/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:20:19 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/08 14:21:06 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

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
	int		y;
	int		x;

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

static void	update_animations(t_app *app)
{
	struct timeval	tv;
	long			now;
	long			dt_ms;

	gettimeofday(&tv, NULL);
	now = (long)tv.tv_sec * 1000L + (long)(tv.tv_usec / 1000L);
	dt_ms = now - app->last_anim_time_ms;
	if (dt_ms < 0)
		dt_ms = 0;
	app->last_anim_time_ms = now;
	app->torch_anim_accum_ms = app->torch_anim_accum_ms + dt_ms;
	while (app->torch_anim_accum_ms >= app->torch_frame_ms)
	{
		app->torch_anim_accum_ms = \
			app->torch_anim_accum_ms - app->torch_frame_ms;
		if (app->cfg.torch_frame_count > 0)
		{
			app->torch_frame_index = app->torch_frame_index + 1;
			if (app->torch_frame_index >= app->cfg.torch_frame_count)
				app->torch_frame_index = 0;
		}
	}
}

int	render_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app->running)
		return (0);
	update_animations(app);
	update_player(app);
	draw_background(&app->frame, app->cfg.ceiling.argb, app->cfg.floor.argb);
	raycast_frame(app);
	draw_sprites(app);
	draw_minimap(app);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.handle, 0, 0);
	draw_hud(app);
	return (0);
}
