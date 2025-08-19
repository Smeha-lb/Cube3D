/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ERROR);
	game->win_ptr = mlx_new_window(game->mlx_ptr, SCREEN_WIDTH, 
		SCREEN_HEIGHT, "Cube3D");
	if (!game->win_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		return (ERROR);
	}
	game->screen_img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->screen_img)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		return (ERROR);
	}
	game->screen_addr = mlx_get_data_addr(game->screen_img,
		&game->screen_bits_per_pixel,
		&game->screen_line_length,
		&game->screen_endian);
	// Hide cursor and center it initially
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	game->mouse_prev_x = SCREEN_WIDTH / 2;
	game->mouse_initialized = 1;
	mlx_hook(game->win_ptr, 17, 0, handle_close, game);
	// Use explicit hooks for KeyPress and KeyRelease (X11)
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	// Mouse motion (PointerMotionMask)
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
	// Constrain mouse by re-centering frequently via loop hook processing
	mlx_loop_hook(game->mlx_ptr, render_frame, game);
	return (SUCCESS);
}

int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
