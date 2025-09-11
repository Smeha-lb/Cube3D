/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:02:20 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 15:54:54 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_sprites(t_map *m)
{
	int	y;
	int	x;
	int	c;

	y = 0;
	c = 0;
	while (y < m->height)
	{
		x = 0;
		while (m->grid[y][x])
		{
			if (m->grid[y][x] == 'T')
				c++;
			x++;
		}
		y++;
	}
	return (c);
}

static void	fill_sprites_row(t_config *cfg, int y, int *i)
{
	int	x;

	x = 0;
	while (cfg->map.grid[y][x])
	{
		if (cfg->map.grid[y][x] == 'T')
		{
			cfg->sprites[*i].x = x + 0.5;
			cfg->sprites[*i].y = y + 0.5;
			*i = *i + 1;
		}
		x++;
	}
}

static void	fill_sprites(t_config *cfg)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < cfg->map.height)
	{
		fill_sprites_row(cfg, y, &i);
		y++;
	}
}

int	init_sprites(t_config *cfg)
{
	cfg->num_sprites = count_sprites(&cfg->map);
	if (cfg->num_sprites <= 0)
		return (0);
	cfg->sprites = (t_sprite *)malloc(sizeof(t_sprite) * cfg->num_sprites);
	if (!cfg->sprites)
		return (1);
	fill_sprites(cfg);
	return (0);
}
