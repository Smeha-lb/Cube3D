/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_torch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:00:00 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/10 13:45:18 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_torch_frames(void *mlx, t_config *cfg)
{
	int			i;
	const char	*paths[TORCH_MAX_FRAMES] = {
		"./textures/torch_0.xpm",
		"./textures/torch_1.xpm",
		"./textures/torch_2.xpm",
		"./textures/torch_3.xpm",
		"./textures/torch_4.xpm",
		"./textures/torch_5.xpm",
		"./textures/torch_6.xpm",
		"./textures/torch_7.xpm"
	};

	cfg->torch_frame_count = 0;
	i = 0;
	while (i < TORCH_MAX_FRAMES)
	{
		cfg->torch_frames[i].path = (char *)paths[i];
		if (load_one(mlx, &cfg->torch_frames[i]) == 0)
			cfg->torch_frame_count = cfg->torch_frame_count + 1;
		else
			break ;
		i++;
	}
	return (0);
}

void	load_torch_texture(void *mlx, t_config *cfg)
{
	if (!cfg->tex_torch.path)
		cfg->tex_torch.path = my_strdup("./textures/torch_0.xpm");
	if (cfg->tex_torch.path)
	{
		if (load_one(mlx, &cfg->tex_torch))
		{
			print_error(
				"Failed to load torch texture. Ensure textures/torch_0.xpm\n");
			free(cfg->tex_torch.path);
			cfg->tex_torch.path = my_strdup("./textures/torch.xpm");
			if (cfg->tex_torch.path)
			{
				if (load_one(mlx, &cfg->tex_torch))
					print_error(
						"Failed to load fallback textures/torch.xpm.\n");
			}
		}
	}
}
