/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:22:16 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/11 15:22:32 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"

# define WIN_W 1920
# define WIN_H 1080

/* Animation */
# define TORCH_MAX_FRAMES 8
# define TORCH_FRAME_MS 120

/* UI/Minimap colors */
# define COLOR_MINIMAP_EMPTY 0x202020
# define COLOR_MINIMAP_WALL 0x5A5A5A
# define COLOR_MINIMAP_DOOR 0x8B5A2B
# define COLOR_MINIMAP_PLAYER 0xFF3333

/* Terminal colors */
# define T_COL_RESET "\033[0m"
# define T_COL_RED "\033[31m"
# define T_COL_GREEN "\033[32m"
# define T_COL_YELLOW "\033[33m"
# define T_COL_BLUE "\033[34m"

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define VALID_MAP_CHARS "NWSETD01T"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	argb;
}	t_color;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
	char	*path;
}	t_texture;

typedef struct s_image
{
	void	*handle;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_app	t_app;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_sprite
{
	double	x;
	double	y;
}	t_sprite;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_config
{
	t_texture	tex_no;
	t_texture	tex_so;
	t_texture	tex_we;
	t_texture	tex_ea;
	t_texture	tex_door;
	t_texture	tex_torch;
	t_texture	torch_frames[TORCH_MAX_FRAMES];
	int			torch_frame_count;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_sprite	*sprites;
	int			num_sprites;
}	t_config;

struct s_app
{
	void		*mlx;
	void		*win;
	t_image		frame;
	int			running;
	t_keys		keys;
	t_config	cfg;
	t_player	player;
	int			last_mouse_x;
	double		zbuf[WIN_W];
	int			torch_count;
	int			hud_msg_timer;
	int			total_torches;
	int			torch_frame_index;
	long		torch_anim_accum_ms;
	int			torch_frame_ms;
	long		last_anim_time_ms;
	double		base_move_speed;
	double		base_rot_speed;
	long		last_time_ms;
};

typedef struct s_sprite_col
{
	int	x;
	int	y0;
	int	y1;
	int	tex_x;
}	t_sprite_col;
typedef struct s_sprite_stripes
{
	int		x;
	int		sw;
	int		dy0;
	int		dy1;
	double	depth;
	/* precomputed sampling */
	double	tx_step;
	double	tpos_start;
	int		tex_w;
}	t_sprite_stripes;


typedef struct s_ray
{
	int			x;
	double		cam_x;
	double		rdx;
	double		rdy;
	int			map_x;
	int			map_y;
	double		sdx;
	double		sdy;
	double		ddx;
	double		ddy;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		pwd;
	int			line_h;
	int			draw_s;
	int			draw_e;
	double		wall_x;
	t_texture	*tx;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			color;
}	t_ray;

int			app_init(t_app *app, const char *map_path);
void		app_cleanup(t_app *app);
int			on_destroy(void *param);
int			on_key_press(int keycode, void *param);
int			on_key_release(int keycode, void *param);
int			render_loop(void *param);
void		prepare_texture(t_app *app, t_ray *r);
void		render_column(t_app *app, t_ray *r);
int			get_tex_color(t_texture *tx, int x, int y);
void		compute_column_params(t_app *app, t_ray *r);
void		walk_until_hit(t_app *app, t_ray *r);
void		setup_ray(t_app *app, t_ray *r);
int			load_one(void *mlx, t_texture *tx);
t_texture	*pick_side(t_app *app, int side,
				double ray_dir_x, double ray_dir_y);

/* parser helpers */
int			parse_rgb(const char *s, t_color *out);
int			assign_path(char **dst, const char *src);
int			parse_identifier(char *line, t_config *cfg);
int			find_map_start(char **lines, int n);
int			copy_map(char **lines, int start, int n, t_map *map);
int			scan_player(t_map *m);
bool		validate_map_only_chars(char **lines, int start, int end);

/* parser */
int			parse_cub_file(const char *path, t_config *cfg);
void		free_config(t_config *cfg);
int			load_textures(void *mlx, t_config *cfg);
void		destroy_textures(void *mlx, t_config *cfg);
int			read_file_lines(const char *path, char ***out_lines, int *out_n);
int			split_lines(const char *acc, char ***out_lines, int *out_n);
int			free_lines(char **lines);
int			parse_texture_keys(char *line, t_config *cfg);

/* movement */
void		update_player(t_app *app);
int			map_is_wall(t_map *map, int x, int y);
void		init_player_from_map(t_app *app);
int			validate_map_closed(t_map *m);
int			compute_move_delta(t_app *app, double *dx, double *dy);
void		try_move_player(t_app *app, double nx, double ny);
void		apply_rotation_from_keys(t_app *app);
void		limit_by_len(double *dx, double *dy, double s);
void		add_right(t_app *app, double *dx, double *dy, double s);
void		update_time_and_speeds(t_app *app);
void		add_forward(t_app *app, double *dx, double *dy, double s);
void		add_backward(t_app *app, double *dx, double *dy, double s);
void		add_left(t_app *app, double *dx, double *dy, double s);


/* rendering */
void		raycast_frame(t_app *app);
void		draw_minimap(t_app *app);
void		draw_hud(t_app *app);
void		draw_sprites(t_app *app);

/* sprites */
int			init_sprites(t_config *cfg);
void		pickup_sprites_near_player(t_app *app);
void		render_one_sprite(t_app *app, t_sprite *s);
void		sort_sprites_by_depth(t_app *app);

/* textures torch helpers */
int			load_torch_frames(void *mlx, t_config *cfg);
void		load_torch_texture(void *mlx, t_config *cfg);
void		destroy_one(void *mlx, t_texture *tx);
void		set_dir_plane(t_player *p, char d);

/* sprite draw helpers */
int			compute_sprite_stripes(t_app *app, t_sprite *s,
				t_sprite_stripes *out);
void		render_sprite_stripes(t_app *app, t_sprite_stripes s);

/* sprite utils */
int			get_sprite_color(t_texture *tx, int x, int y);
t_texture	*choose_torch_texture(t_app *app);
void		store_sprite_pixel(t_app *app, int x, int y, int color);

/* doors */
void		toggle_door_in_front(t_app *app);

/* mouse */
int			on_mouse_move(int x, int y, void *param);

/* utils */
char		*my_strdup(const char *s);
size_t		my_strlen(const char *s);
int			print_error(char *msg);
int			my_strncmp(const char *a, const char *b, size_t n);
int			my_is_space(int c);
int			my_atoi(const char *s, int *out);
bool		is_valid_map_char(char c);

/* app init helpers */
void		image_clear(t_image *img);
void		zero_config(t_config *cfg);
void		zero_keys(t_keys *k);
void		center_mouse(t_app *app);
int			setup_mlx_and_window(t_app *app);
int			setup_frame(t_app *app);
void		init_time_now(t_app *app);
void		setup_animation_defaults(t_app *app);
void		setup_hooks(t_app *app);

#endif
