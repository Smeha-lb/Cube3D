#include "../includes/cub3d.h"
#include <string.h>
#include <sys/time.h>

static void	image_clear(t_image *img)
{
	int	i;
	int	size;

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

static void	zero_config(t_config *cfg)
{
	cfg->tex_no.path = NULL;
	cfg->tex_so.path = NULL;
	cfg->tex_we.path = NULL;
	cfg->tex_ea.path = NULL;
	cfg->tex_no.img = NULL;
	cfg->tex_so.img = NULL;
	cfg->tex_we.img = NULL;
	cfg->tex_ea.img = NULL;
	cfg->tex_door.path = NULL;
	cfg->tex_door.img = NULL;
	cfg->tex_torch.path = my_strdup("textures/torch.xpm");
	cfg->tex_torch.img = NULL;
	cfg->map.grid = NULL;
	cfg->sprites = NULL;
	cfg->num_sprites = 0;
}

static void	zero_keys(t_keys *k)
{
	k->w = 0;
	k->a = 0;
	k->s = 0;
	k->d = 0;
	k->left = 0;
	k->right = 0;
}

static void	center_mouse(t_app *app)
{
	mlx_mouse_move(app->mlx, app->win, WIN_W / 2, WIN_H / 2);
	app->last_mouse_x = WIN_W / 2;
}

int	app_init(t_app *app, const char *map_path)
{
	if (!app)
		return (1);
	zero_config(&app->cfg);
	zero_keys(&app->keys);
	app->last_mouse_x = -1;
	if (parse_cub_file(map_path, &app->cfg))
		return (1);
	app->mlx = mlx_init();
	if (!app->mlx)
		return (1);
	app->win = mlx_new_window(app->mlx, WIN_W, WIN_H, "cub3D");
	if (!app->win)
		return (1);
	mlx_mouse_hide(app->mlx, app->win);
	center_mouse(app);
	app->frame.handle = mlx_new_image(app->mlx, WIN_W, WIN_H);
	if (!app->frame.handle)
		return (1);
	app->frame.addr = mlx_get_data_addr(app->frame.handle, &app->frame.bpp, &app->frame.line_len, &app->frame.endian);
	if (!app->frame.addr)
		return (1);
	image_clear(&app->frame);
	app->running = 1;
	if (load_textures(app->mlx, &app->cfg))
		return (1);
	if (init_sprites(&app->cfg))
        return (1);
	init_player_from_map(app);
	app->torch_count = 0;
	app->hud_msg_timer = 0;
	app->total_torches = app->cfg.num_sprites;
	app->base_move_speed = 2.5;
	app->base_rot_speed = 1.5;
	{
		struct timeval tv;
		long ms;

		gettimeofday(&tv, NULL);
		ms = (long)tv.tv_sec * 1000L + (long)(tv.tv_usec / 1000L);
		app->last_time_ms = ms;
	}
	mlx_loop_hook(app->mlx, render_loop, app);
	mlx_hook(app->win, 17, 0, on_destroy, app);
	mlx_hook(app->win, 2, 1L<<0, on_key_press, app);
	mlx_hook(app->win, 3, 1L<<1, on_key_release, app);
	mlx_hook(app->win, 6, 1L<<6, on_mouse_move, app);
	return (0);
}
