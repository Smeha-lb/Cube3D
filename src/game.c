/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	int	i;

	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->screen_img = NULL;
	game->screen_addr = NULL;
	game->mouse_captured = 1;
	game->warping_mouse = 0;
	game->mouse_initialized = 0;
	game->mouse_prev_x = SCREEN_WIDTH / 2;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
		game->textures[i].path = NULL;
		i++;
	}
	i = 0;
	while (i < 65536)
	{
		game->keys[i] = 0;
		i++;
	}
	init_player(game);
}

void	init_player(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = FOV;
}

void	cleanup_game(t_game *game)
{
	cleanup_resources(game);
}

void	cleanup_resources(t_game *game)
{
	int	i;

	if (game->map)
		ft_free_array(game->map);
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx_ptr, game->textures[i].img);
		if (game->textures[i].path)
			free(game->textures[i].path);
		i++;
	}
	if (game->screen_img)
		mlx_destroy_image(game->mlx_ptr, game->screen_img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
}

void	error_exit(t_game *game, const char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	cleanup_game(game);
	exit(1);
}
