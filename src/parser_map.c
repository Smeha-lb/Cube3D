/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:56:12 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 14:54:42 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_map_start(char **lines, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (lines[i][0] == '1' || lines[i][0] == '0' || lines[i][0] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

static int	copy_one_row(t_map *map, char *src, int *out_w)
{
	int	w;

	map->grid[*out_w] = my_strdup(src);
	if (!map->grid[*out_w])
		return (1);
	w = (int)my_strlen(map->grid[*out_w]);
	if (w > map->width)
		map->width = w;
	*out_w = *out_w + 1;
	return (0);
}

int	copy_map(char **lines, int start, int n, t_map *map)
{
	int		i;
	int		h;
	int		row;

	h = n - start;
	map->grid = (char **)malloc(sizeof(char *) * (h + 1));
	if (!map->grid)
		return (1);
	map->height = h;
	map->width = 0;
	i = 0;
	row = 0;
	while (i < h)
	{
		if (copy_one_row(map, lines[start + i], &row))
			return (1);
		i++;
	}
	map->grid[h] = NULL;
	return (0);
}

static int	scan_row_for_player(t_map *m, int y, int *found)
{
	int	x;

	x = 0;
	while (m->grid[y][x])
	{
		if (m->grid[y][x] == 'N' || m->grid[y][x] == 'S'
			|| m->grid[y][x] == 'E' || m->grid[y][x] == 'W')
		{
			m->player_x = x;
			m->player_y = y;
			m->player_dir = m->grid[y][x];
			*found = *found + 1;
		}
		x++;
	}
	return (0);
}

int	scan_player(t_map *m)
{
	int	y;
	int	found;

	y = 0;
	found = 0;
	while (y < m->height)
	{
		scan_row_for_player(m, y, &found);
		y++;
	}
	if (found == 1)
		return (0);
	return (1);
}

/* moved to parser_utils.c */
