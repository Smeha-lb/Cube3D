/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_frame(t_game *game)
{
	handle_movement(game);
	process_mouse_look(game);
	// Draw background first
	render_floor_ceiling(game);
	// Then draw walls on top
	cast_rays(game);
	// Present single buffered image
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->screen_img, 0, 0);
	return (0);
}

void	render_walls(t_game *game, t_ray *ray, int x)
{
	int		wall_height;
	int		wall_start;
	int		wall_end;

	wall_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	wall_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_end >= SCREEN_HEIGHT)
		wall_end = SCREEN_HEIGHT - 1;
	apply_texture(game, ray, x, wall_height);
}

void	render_floor_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	offset;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			offset = y * game->screen_line_length + x * (game->screen_bits_per_pixel / 8);
			if (y < SCREEN_HEIGHT / 2)
				*(int *)(game->screen_addr + offset) = game->ceiling_color;
			else
				*(int *)(game->screen_addr + offset) = game->floor_color;
			x++;
		}
		y++;
	}
}

void	render_walls_to_buffer(t_game *game, t_ray *ray, int x)
{
	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		texture_index;
	t_texture	*tex;
	int		tex_x;
	double		step;
	double		tex_pos;
	int		y;
	int		tex_y;
	int		color;
	int		screen_offset;

	if (ray->perp_wall_dist < 1e-6)
		ray->perp_wall_dist = 1e-6;
	wall_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	wall_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_end >= SCREEN_HEIGHT)
		wall_end = SCREEN_HEIGHT - 1;

	texture_index = get_wall_texture_index(ray);
	tex = &game->textures[texture_index];

	// Calculate exact wall hit position (for texture X coordinate)
	double wall_x;
	if (ray->hit_side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	// Flip texture horizontally when needed
	if ((ray->hit_side == 0 && ray->ray_dir_x > 0) || (ray->hit_side == 1 && ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;

	// How much to increase texture coordinate per screen pixel
	step = (double)tex->height / (double)wall_height;
	tex_pos = (wall_start - SCREEN_HEIGHT / 2 + wall_height / 2) * step;

	for (y = wall_start; y <= wall_end; y++)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = get_texture_color(tex, tex_x, tex_y);
		// Simple shading: darken when hitting a Y-side to give depth
		if (ray->hit_side == 1)
			color = (color >> 1) & 0x7F7F7F;
		screen_offset = y * game->screen_line_length + x * (game->screen_bits_per_pixel / 8);
		*(int *)(game->screen_addr + screen_offset) = color;
	}
}

void	render_walls_to_image(t_game *game)
{
	(void)game;
	// This function will be called after cast_rays to render walls to the image buffer
	// For now, it's empty as walls are rendered directly in cast_rays
}

void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		y++;
	}
}
