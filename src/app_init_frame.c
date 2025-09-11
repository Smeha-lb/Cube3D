/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init_frame.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:26:00 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 13:39:26 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	image_clear(t_image *img)
{
	int		i;
	int		size;

	if (!img || !img->addr)
		return ;
	size = img->line_len * WIN_H;
	i = 0;
	while (i < size)
	{
		img->addr[i] = 0;
		i++;
	}
}

int	setup_frame(t_app *app)
{
	app->frame.handle = mlx_new_image(app->mlx, WIN_W, WIN_H);
	if (!app->frame.handle)
		return (1);
	app->frame.addr = mlx_get_data_addr(app->frame.handle,
			&app->frame.bpp, &app->frame.line_len, &app->frame.endian);
	if (!app->frame.addr)
		return (1);
	image_clear(&app->frame);
	return (0);
}
