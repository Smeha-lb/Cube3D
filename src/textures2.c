/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:01:08 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/09 16:18:30 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_textures(void *mlx, t_config *cfg)
{
	int		i;

	destroy_one(mlx, &cfg->tex_no);
	destroy_one(mlx, &cfg->tex_so);
	destroy_one(mlx, &cfg->tex_we);
	destroy_one(mlx, &cfg->tex_ea);
	destroy_one(mlx, &cfg->tex_door);
	destroy_one(mlx, &cfg->tex_torch);
	i = 0;
	while (i < cfg->torch_frame_count)
	{
		destroy_one(mlx, &cfg->torch_frames[i]);
		i++;
	}
}
