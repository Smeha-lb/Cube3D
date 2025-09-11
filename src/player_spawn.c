/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:46 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:32:01 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_dir_north(t_player *p)
{
	p->dir_x = 0;
	p->dir_y = -1;
	p->plane_x = 0.66;
	p->plane_y = 0;
}

static void	set_dir_south(t_player *p)
{
	p->dir_x = 0;
	p->dir_y = 1;
	p->plane_x = -0.66;
	p->plane_y = 0;
}

static void	set_dir_east(t_player *p)
{
	p->dir_x = 1;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0.66;
}

static void	set_dir_west(t_player *p)
{
	p->dir_x = -1;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = -0.66;
}

void	set_dir_plane(t_player *p, char d)
{
	if (d == 'N')
		set_dir_north(p);
	else if (d == 'S')
		set_dir_south(p);
	else if (d == 'E')
		set_dir_east(p);
	else
		set_dir_west(p);
}
