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
	if (cfg->tex_torch.path && load_one(mlx, &cfg->tex_torch))
		return (1);
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


