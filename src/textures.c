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
}


