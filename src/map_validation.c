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

static void	free_grid(char **grid, int h)
{
	int y;
	y = 0;
	while (y < h)
	{
		free(grid[y]);
		y++;
	}
	free(grid);
}

static int	build_rect_grid(t_game *game, char ***out_grid, int *w, int *h)
{
	char	**grid;
	int		y;
	int		x;
	int		len;

	*w = game->map_width;
	*h = game->map_height;
	grid = (char **)malloc(sizeof(char *) * (*h));
	if (!grid)
		return (ERROR);
	y = 0;
	while (y < *h)
	{
		grid[y] = (char *)malloc(sizeof(char) * (*w));
		if (!grid[y])
			return (ERROR);
		len = ft_strlen(game->map[y]);
		x = 0;
		while (x < *w)
		{
			grid[y][x] = (x < len) ? game->map[y][x] : ' ';
			x++;
		}
		y++;
	}
	*out_grid = grid;
	return (SUCCESS);
}

// Respect indentation: for each row, the first and last non-space must be '1'
static int	validate_row_borders_nonspace(char **grid, int w, int h)
{
	int y;
	int x;
	int left;
	int right;

	y = 0;
	while (y < h)
	{
		left = -1;
		right = -1;
		x = 0;
		while (x < w)
		{
			if (grid[y][x] != ' ')
			{
				left = x;
				break ;
			}
			x++;
		}
		x = w - 1;
		while (x >= 0)
		{
			if (grid[y][x] != ' ')
			{
				right = x;
				break ;
			}
			x--;
		}
		if (left != -1 && right != -1)
		{
			if (grid[y][left] != '1' || grid[y][right] != '1')
				return (ERROR);
		}
		y++;
	}
	return (SUCCESS);
}

static int	validate_zero_adjacency(char **grid, int w, int h)
{
	int	x;
	int	y;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (grid[y][x] == '0')
			{
				if (y - 1 < 0 || (grid[y - 1][x] != '0' && grid[y - 1][x] != '1'))
					return (ERROR);
				if (y + 1 >= h || (grid[y + 1][x] != '0' && grid[y + 1][x] != '1'))
					return (ERROR);
				if (x - 1 < 0 || (grid[y][x - 1] != '0' && grid[y][x - 1] != '1'))
					return (ERROR);
				if (x + 1 >= w || (grid[y][x + 1] != '0' && grid[y][x + 1] != '1'))
					return (ERROR);
			}
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int	validate_map(t_game *game)
{
	int		i;
	int		j;
	int		player_count;
	char		**grid;
	int		w;
	int		h;

	if (!game->map || game->map_height < 3)
		return (ERROR);
	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_char(game->map[i][j]) && game->map[i][j] != ' ')
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

	if (build_rect_grid(game, &grid, &w, &h) != SUCCESS)
		return (ERROR);
	if (validate_row_borders_nonspace(grid, w, h) != SUCCESS)
	{
		free_grid(grid, h);
		return (ERROR);
	}
	if (validate_zero_adjacency(grid, w, h) != SUCCESS)
	{
		free_grid(grid, h);
		return (ERROR);
	}
	free_grid(grid, h);
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
