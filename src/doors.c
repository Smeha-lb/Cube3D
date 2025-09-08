/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:18:51 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/08 14:19:22 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	cell(t_map *m, int x, int y)
{
	if (y < 0 || y >= m->height)
		return ('1');
	if (x < 0)
		return ('1');
	if (x >= (int)my_strlen(m->grid[y]))
		return ('1');
	return (m->grid[y][x]);
}

void	toggle_door_in_front(t_app *app)
{
	int		tx;
	int		ty;
	double	px;
	double	py;
	char	c;

	px = app->player.x + app->player.dir_x * 0.8;
	py = app->player.y + app->player.dir_y * 0.8;
	tx = (int)px;
	ty = (int)py;
	c = cell(&app->cfg.map, tx, ty);
	if (c == '1' || c == '0')
		return ;
	if (c == 'D')
		app->cfg.map.grid[ty][tx] = '0';
	else
		app->cfg.map.grid[ty][tx] = 'D';
}
