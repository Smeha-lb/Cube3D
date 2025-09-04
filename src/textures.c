#include "../includes/cub3d.h"

static int	load_one(void *mlx, t_texture *tx)
{
	if (!tx->path)
		return (1);
	tx->img = mlx_xpm_file_to_image(mlx, tx->path, &tx->w, &tx->h);
	if (!tx->img)
		return (1);
	tx->addr = mlx_get_data_addr(tx->img, &tx->bpp, &tx->line_len, &tx->endian);
	if (!tx->addr)
		return (1);
	return (0);
}

static int	load_torch_frames(void *mlx, t_config *cfg)
{
    int i;
    const char *paths[TORCH_MAX_FRAMES] = {
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

int		load_textures(void *mlx, t_config *cfg)
{
	if (load_one(mlx, &cfg->tex_no))
		return (1);
	if (load_one(mlx, &cfg->tex_so))
		return (1);
	if (load_one(mlx, &cfg->tex_we))
		return (1);
	if (load_one(mlx, &cfg->tex_ea))
		return (1);
	if (cfg->tex_door.path && load_one(mlx, &cfg->tex_door))
		return (1);
	/* Torch texture is optional: use default if not provided, don't abort on failure */
	if (!cfg->tex_torch.path)
		cfg->tex_torch.path = my_strdup("./textures/torch_0.xpm");
	if (cfg->tex_torch.path)
	{
		if (load_one(mlx, &cfg->tex_torch))
		{
			print_error("Failed to load torch texture. Ensure textures/torch_0.xpm exists and run from project root.\n");
			free(cfg->tex_torch.path);
			cfg->tex_torch.path = my_strdup("./textures/torch.xpm");
			if (cfg->tex_torch.path)
			{
				if (load_one(mlx, &cfg->tex_torch))
					print_error("Failed to load fallback torch texture textures/torch.xpm.\n");
			}
		}
	}
	load_torch_frames(mlx, cfg);
	return (0);
}

static void	destroy_one(void *mlx, t_texture *tx)
{
	if (tx->img)
		mlx_destroy_image(mlx, tx->img);
}

void	destroy_textures(void *mlx, t_config *cfg)
{
	destroy_one(mlx, &cfg->tex_no);
	destroy_one(mlx, &cfg->tex_so);
	destroy_one(mlx, &cfg->tex_we);
	destroy_one(mlx, &cfg->tex_ea);
	destroy_one(mlx, &cfg->tex_door);
	destroy_one(mlx, &cfg->tex_torch);
    {
        int i;

        i = 0;
        while (i < cfg->torch_frame_count)
        {
            destroy_one(mlx, &cfg->torch_frames[i]);
            i++;
        }
    }
}


