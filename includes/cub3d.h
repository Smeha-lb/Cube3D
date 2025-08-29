#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"

# define WIN_W 800
# define WIN_H 600

typedef struct s_color
{
	int r;
	int g;
	int b;
	int argb;
} t_color;

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
} t_texture;

typedef struct s_image
{
	void	*handle;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}t_image;

typedef struct s_app t_app;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
} t_map;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
} t_keys;

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
} t_player;

typedef struct s_config
{
	t_texture	tex_no;
	t_texture	tex_so;
	t_texture	tex_we;
	t_texture	tex_ea;
	t_texture	tex_door;
	t_color	floor;
	t_color	ceiling;
	t_map		map;
} t_config;

struct s_app
{
	void	*mlx;
	void	*win;
	t_image	frame;
	int		running;
	t_keys	keys;
	t_config	cfg;
	t_player	player;
	int		last_mouse_x;
};

int		app_init(t_app *app, const char *map_path);
void	app_cleanup(t_app *app);
int		on_destroy(void *param);
int		on_key_press(int keycode, void *param);
int		on_key_release(int keycode, void *param);
int		render_loop(void *param);

/* parser */
int		parse_cub_file(const char *path, t_config *cfg);
void	free_config(t_config *cfg);
int		load_textures(void *mlx, t_config *cfg);
void	destroy_textures(void *mlx, t_config *cfg);
int		read_file_lines(const char *path, char ***out_lines, int *out_n);
int		free_lines(char **lines);

/* movement */
void	update_player(t_app *app);
int		map_is_wall(t_map *map, int x, int y);
void	init_player_from_map(t_app *app);
int		validate_map_closed(t_map *m);

/* rendering */
void	raycast_frame(t_app *app);
void	draw_minimap(t_app *app);
void	draw_hud(t_app *app);

/* doors */
void	toggle_door_in_front(t_app *app);

/* mouse */
int		on_mouse_move(int x, int y, void *param);

/* utils */
size_t	my_strlen(const char *s);
int		my_strncmp(const char *a, const char *b, size_t n);
char	*my_strdup(const char *s);
int		my_is_space(int c);
int		my_atoi(const char *s, int *out);

#endif
