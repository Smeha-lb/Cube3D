/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:21:45 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/09 13:08:51 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	destroy_image(void *mlx, t_image *img)
{
	if (img && img->handle)
		mlx_destroy_image(mlx, img->handle);
}

void	app_cleanup(t_app *app)
{
	if (!app)
		return ;
	destroy_textures(app->mlx, &app->cfg);
	free_config(&app->cfg);
	destroy_image(app->mlx, &app->frame);
	mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
}
