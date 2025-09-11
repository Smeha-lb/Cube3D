/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:09:46 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/11 15:30:54 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_one_sprite(t_app *app, t_sprite *s)
{
	t_sprite_stripes	ss;

	if (compute_sprite_stripes(app, s, &ss) != 0)
		return ;
	render_sprite_stripes(app, ss);
}

void	draw_sprites(t_app *app)
{
	int		i;

	if (app->cfg.num_sprites <= 0)
		return ;
	if (!app->cfg.tex_torch.img && app->cfg.torch_frame_count <= 0)
		return ;
	sort_sprites_by_depth(app);
	i = 0;
	while (i < app->cfg.num_sprites)
	{
		render_one_sprite(app, &app->cfg.sprites[i]);
		i++;
	}
}
