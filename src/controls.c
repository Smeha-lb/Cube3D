/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	if (keycode == KEY_M)
	{
		game->mouse_captured = !game->mouse_captured;
		if (game->mouse_captured)
		{
			mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
			game->warping_mouse = 1;
			mlx_mouse_move(game->mlx_ptr, game->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}
		else
		{
			mlx_mouse_show(game->mlx_ptr, game->win_ptr);
		}
		return (0);
	}
	game->keys[keycode] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	game->keys[keycode] = 0;
	return (0);
}

void	handle_movement(t_game *game)
{
	if (game->keys[KEY_W])
		move_forward(game);
	if (game->keys[KEY_S])
		move_backward(game);
	if (game->keys[KEY_A])
		move_left(game);
	if (game->keys[KEY_D])
		move_right(game);
	if (game->keys[KEY_LEFT])
		rotate_left(game);
	if (game->keys[KEY_RIGHT])
		rotate_right(game);
}

void	move_forward(t_game *game)
{
	double	step_x;
	double	step_y;

	step_x = game->player.dir_x * MOVE_SPEED;
	step_y = game->player.dir_y * MOVE_SPEED;
	// try X axis
	if (game->map[(int)(game->player.y)][(int)(game->player.x + step_x)] != '1')
		game->player.x += step_x;
	// then Y axis
	if (game->map[(int)(game->player.y + step_y)][(int)(game->player.x)] != '1')
		game->player.y += step_y;
}

void	move_backward(t_game *game)
{
	double	step_x;
	double	step_y;

	step_x = -game->player.dir_x * MOVE_SPEED;
	step_y = -game->player.dir_y * MOVE_SPEED;
	if (game->map[(int)(game->player.y)][(int)(game->player.x + step_x)] != '1')
		game->player.x += step_x;
	if (game->map[(int)(game->player.y + step_y)][(int)(game->player.x)] != '1')
		game->player.y += step_y;
}

void	move_left(t_game *game)
{
	double	step_x;
	double	step_y;

	step_x = -game->player.plane_x * MOVE_SPEED;
	step_y = -game->player.plane_y * MOVE_SPEED;
	if (game->map[(int)(game->player.y)][(int)(game->player.x + step_x)] != '1')
		game->player.x += step_x;
	if (game->map[(int)(game->player.y + step_y)][(int)(game->player.x)] != '1')
		game->player.y += step_y;
}

void	move_right(t_game *game)
{
	double	step_x;
	double	step_y;

	step_x = game->player.plane_x * MOVE_SPEED;
	step_y = game->player.plane_y * MOVE_SPEED;
	if (game->map[(int)(game->player.y)][(int)(game->player.x + step_x)] != '1')
		game->player.x += step_x;
	if (game->map[(int)(game->player.y + step_y)][(int)(game->player.x)] != '1')
		game->player.y += step_y;
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED) 
		- game->player.dir_y * sin(ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) 
		+ game->player.dir_y * cos(ROTATION_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED) 
		- game->player.plane_y * sin(ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(ROTATION_SPEED) 
		+ game->player.plane_y * cos(ROTATION_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(-ROTATION_SPEED) 
		- game->player.dir_y * sin(-ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) 
		+ game->player.dir_y * cos(-ROTATION_SPEED);
	game->player.plane_x = game->player.plane_x * cos(-ROTATION_SPEED) 
		- game->player.plane_y * sin(-ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED) 
		+ game->player.plane_y * cos(-ROTATION_SPEED);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (game->warping_mouse)
	{
		game->warping_mouse = 0;
		return (0);
	}
	if (!game->mouse_initialized)
	{
		game->mouse_initialized = 1;
		game->warping_mouse = 1;
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		return (0);
	}
	if (!game->mouse_captured)
		return (0);

	int center_x = SCREEN_WIDTH / 2;
	int dx = x - center_x;
	if (dx != 0)
	{
		double angle = (double)dx * MOUSE_SENSITIVITY;
		double old_dir_x = game->player.dir_x;
		double old_plane_x = game->player.plane_x;
		game->player.dir_x = game->player.dir_x * cos(angle)
			- game->player.dir_y * sin(angle);
		game->player.dir_y = old_dir_x * sin(angle)
			+ game->player.dir_y * cos(angle);
		game->player.plane_x = game->player.plane_x * cos(angle)
			- game->player.plane_y * sin(angle);
		game->player.plane_y = old_plane_x * sin(angle)
			+ game->player.plane_y * cos(angle);
	}
	// Recenter immediately to keep cursor locked to window
	game->warping_mouse = 1;
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, center_x, SCREEN_HEIGHT / 2);
	return (0);
}

// Option 2: recenter in loop hook instead of motion callback to reduce jitter
int	process_mouse_look(t_game *game)
{
	(void)game;
	return (0);
}
