#include "../includes/cub3d.h"

static int count_sprites(t_map *m)
{
	int y;
	int x;
	int c;

	y = 0;
	c = 0;
	while (y < m->height)
	{
		x = 0;
		while (m->grid[y][x])
		{
			if (m->grid[y][x] == 'T')
				c++;
			x++;
		}
		y++;
	}
	return (c);
}

static void fill_sprites_row(t_config *cfg, int y, int *i)
{
	int x;

	x = 0;
	while (cfg->map.grid[y][x])
	{
		if (cfg->map.grid[y][x] == 'T')
		{
			cfg->sprites[*i].x = x + 0.5;
			cfg->sprites[*i].y = y + 0.5;
			*i = *i + 1;
		}
		x++;
	}
}

static void fill_sprites(t_config *cfg)
{
	int y;
	int i;

	y = 0;
	i = 0;
	while (y < cfg->map.height)
	{
		fill_sprites_row(cfg, y, &i);
		y++;
	}
}

int init_sprites(t_config *cfg)
{
	cfg->num_sprites = count_sprites(&cfg->map);
	if (cfg->num_sprites <= 0)
		return (0);
	cfg->sprites = (t_sprite *)malloc(sizeof(t_sprite) * cfg->num_sprites);
	if (!cfg->sprites)
		return (1);
	fill_sprites(cfg);
	return (0);
}

static int clamp(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static int get_sprite_color(t_texture *tx, int x, int y)
{
	char *p;

	x = clamp(x, 0, tx->w - 1);
	y = clamp(y, 0, tx->h - 1);
	p = tx->addr + y * tx->line_len + x * (tx->bpp / 8);
	return (*(int *)p);
}

static void blit_sprite_column(t_app *app, int x, int y0, int y1, int tex_x)
{
	int y;
	double step;
	double tpos;
	int color;
	t_texture *tx;

	if (app->cfg.torch_frame_count > 0)
		tx = &app->cfg.torch_frames[app->torch_frame_index % app->cfg.torch_frame_count];
	else
		tx = &app->cfg.tex_torch;
	step = (double)tx->h / (double)(y1 - y0);
	tpos = 0.0;
	y = y0;
	while (y < y1)
	{
		color = get_sprite_color(tx, tex_x, (int)tpos);
		if ((color & 0x00FFFFFF) != 0)
		{
			char *dst;
			dst = app->frame.addr + (y * app->frame.line_len + x * (app->frame.bpp / 8));
			*(unsigned int *)dst = (unsigned int)color;
		}
		tpos += step;
		y++;
	}
}

static void render_sprite_stripes(t_app *app, int sx, int sw, int dy0, int dy1, double depth)
{
	int stripe;
	int tx;
	t_texture *t;

	if (app->cfg.torch_frame_count > 0)
		t = &app->cfg.torch_frames[app->torch_frame_index % app->cfg.torch_frame_count];
	else
		t = &app->cfg.tex_torch;
	stripe = sx - (int)(sw / 2.0);
	if (stripe < 0)
		stripe = 0;
	while (stripe < sx + (int)(sw / 2.0) && stripe < WIN_W)
	{
		double z;

		z = app->zbuf[stripe];
		if (z <= 0.0 || depth < z)
		{
			tx = (int)((stripe - (sx - (int)(sw / 2.0))) * t->w / (double)sw);
			blit_sprite_column(app, stripe, dy0, dy1, tx);
		}
		stripe++;
	}
}

static void render_one_sprite(t_app *app, t_sprite *s)
{
	double spx;
	double spy;
	double inv;
	double tr_x;
	double tr_y;
	int sx;
	int sh;
	int dy0;
	int dy1;

	spx = s->x - app->player.x;
	spy = s->y - app->player.y;
	inv = 1.0 / (app->player.plane_x * app->player.dir_y - app->player.dir_x * app->player.plane_y);
	tr_x = inv * (app->player.dir_y * spx - app->player.dir_x * spy);
	tr_y = inv * (-app->player.plane_y * spx + app->player.plane_x * spy);
	if (tr_y <= 0)
		return ;
	sx = (int)((WIN_W / 2.0) * (1.0 + tr_x / tr_y));
	sh = (int)fabs((double)(WIN_H / tr_y));
	dy0 = -sh / 2 + WIN_H / 2;
	if (dy0 < 0)
		dy0 = 0;
	dy1 = sh / 2 + WIN_H / 2;
	if (dy1 >= WIN_H)
		dy1 = WIN_H - 1;
	render_sprite_stripes(app, sx, sh, dy0, dy1, tr_y);
}

void draw_sprites(t_app *app)
{
	int i;

	if (app->cfg.num_sprites <= 0)
		return ;
	if (!app->cfg.tex_torch.img && app->cfg.torch_frame_count <= 0)
		return ;
	i = 0;
	while (i < app->cfg.num_sprites)
	{
		render_one_sprite(app, &app->cfg.sprites[i]);
		i++;
	}
}


static int sprite_is_close(t_app *app, t_sprite *s)
{
	double dx;
	double dy;
	double d2;

	dx = s->x - app->player.x;
	dy = s->y - app->player.y;
	d2 = dx * dx + dy * dy;
	if (d2 < 0.25)
		return (1);
	return (0);
}

static void remove_sprite_at_index(t_config *cfg, int idx)
{
	int i;

	i = idx;
	while (i + 1 < cfg->num_sprites)
	{
		cfg->sprites[i] = cfg->sprites[i + 1];
		i++;
	}
	cfg->num_sprites--;
}

void pickup_sprites_near_player(t_app *app)
{
	int i;

	i = 0;
	while (i < app->cfg.num_sprites)
	{
		if (sprite_is_close(app, &app->cfg.sprites[i]))
		{
			remove_sprite_at_index(&app->cfg, i);
			app->torch_count = app->torch_count + 1;
			app->hud_msg_timer = 120;
			continue ;
		}
		i++;
	}
}


