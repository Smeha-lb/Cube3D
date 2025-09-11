/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init_time_hooks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:26:08 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 13:38:34 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

void	init_time_now(t_app *app)
{
	struct timeval	v;
	long			ms;

	gettimeofday(&v, NULL);
	ms = (long)v.tv_sec * 1000L + (long)(v.tv_usec / 1000L);
	app->last_time_ms = ms;
}

void	setup_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx, render_loop, app);
	mlx_hook(app->win, 17, 0, on_destroy, app);
	mlx_hook(app->win, 2, 1L << 0, on_key_press, app);
	mlx_hook(app->win, 3, 1L << 1, on_key_release, app);
	mlx_hook(app->win, 6, 1L << 6, on_mouse_move, app);
}
