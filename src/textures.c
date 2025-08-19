/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].path)
		{
			game->textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr,
				game->textures[i].path, &game->textures[i].width,
				&game->textures[i].height);
			if (!game->textures[i].img)
				return (ERROR);
			game->textures[i].addr = mlx_get_data_addr(
				game->textures[i].img,
				&game->textures[i].bits_per_pixel,
				&game->textures[i].line_length,
				&game->textures[i].endian);
		}
		i++;
	}
	return (SUCCESS);
}

void	apply_texture(t_game *game, t_ray *ray, int x, int wall_height)
{
	int		texture_index;
	int		texture_x;
	int		wall_start;
	int		wall_end;
	int		y;
	int		texture_y;
	int		color;

	texture_index = get_wall_texture_index(ray);
	texture_x = get_texture_x(ray, &game->textures[texture_index]);
	wall_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = wall_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_end >= SCREEN_HEIGHT)
		wall_end = SCREEN_HEIGHT - 1;
	y = wall_start;
	while (y < wall_end)
	{
		texture_y = (y - wall_start) * game->textures[texture_index].height 
			/ wall_height;
		color = get_texture_color(&game->textures[texture_index], 
			texture_x, texture_y);
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		y++;
	}
}

int	get_wall_texture_index(t_ray *ray)
{
	if (ray->hit_side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

int	get_texture_x(t_ray *ray, t_texture *texture)
{
	double	wall_x;
	int		texture_x;

	if (ray->hit_side == 0)
		wall_x = ray->map_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->map_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * texture->width);
	if (ray->hit_side == 0 && ray->ray_dir_x > 0)
		texture_x = texture->width - texture_x - 1;
	if (ray->hit_side == 1 && ray->ray_dir_y < 0)
		texture_x = texture->width - texture_x - 1;
	return (texture_x);
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	int	offset;
	int	color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	offset = y * texture->line_length + x * (texture->bits_per_pixel / 8);
	color = *(int *)(texture->addr + offset);
	return (color);
}
