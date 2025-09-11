/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:00:12 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 13:58:14 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	sprite_d2(t_app *app, t_sprite *s)
{
	double	dx;
	double	dy;

	dx = s->x - app->player.x;
	dy = s->y - app->player.y;
	return (dx * dx + dy * dy);
}

static void	swap_sprite(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_sprites_by_depth(t_app *app)
{
	int	i;
	int	j;
	int	n;

	n = app->cfg.num_sprites;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (sprite_d2(app, &app->cfg.sprites[j])
				< sprite_d2(app, &app->cfg.sprites[j + 1]))
				swap_sprite(&app->cfg.sprites[j], &app->cfg.sprites[j + 1]);
			j++;
		}
		i++;
	}
}
