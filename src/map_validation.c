/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	has_player_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_map(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	if (!game->map || game->map_height < 3)
		return (ERROR);
	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_char(game->map[i][j]))
				return (ERROR);
			if (has_player_spawn(game->map[i][j]))
			{
				player_count++;
				if (find_player_spawn(game, i, j) != SUCCESS)
					return (ERROR);
			}
			j++;
		}
		if (j > game->map_width)
			game->map_width = j;
		i++;
	}
	if (player_count != 1)
		return (ERROR);
	if (check_wall_closure(game) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	find_player_spawn(t_game *game, int y, int x)
{
	char	spawn_char;

	spawn_char = game->map[y][x];
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	if (spawn_char == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = FOV;
		game->player.plane_y = 0;
	}
	else if (spawn_char == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -FOV;
		game->player.plane_y = 0;
	}
	else if (spawn_char == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = FOV;
	}
	else if (spawn_char == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -FOV;
	}
	game->map[y][x] = '0';
	return (SUCCESS);
}

int	check_wall_closure(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0' || has_player_spawn(game->map[i][j]))
			{
				if (i == 0 || i == game->map_height - 1 || j == 0)
					return (ERROR);
				if (game->map[i][j + 1] == '\0' || game->map[i][j + 1] == ' ')
					return (ERROR);
				if (game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ')
					return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
