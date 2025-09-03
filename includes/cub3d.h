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

# define VALID_MAP_CHARS "NWSETD01"

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

typedef struct s_sprite
{
	double	x;
	double	y;
} t_sprite;

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
	t_texture	tex_torch;
	t_color	floor;
	t_color	ceiling;
	t_map		map;
	t_sprite	*sprites;
	int		num_sprites;
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
	double	zbuf[WIN_W];
	int		torch_count;
	int		hud_msg_timer;
	int		total_torches;
	double	base_move_speed;
	double	base_rot_speed;
	long	last_time_ms;
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
void	draw_sprites(t_app *app);

/* sprites */
int		init_sprites(t_config *cfg);
void	pickup_sprites_near_player(t_app *app);

/* doors */
void	toggle_door_in_front(t_app *app);

/* mouse */
int		on_mouse_move(int x, int y, void *param);

/* utils */
char	*my_strdup(const char *s);
size_t	my_strlen(const char *s);
int		print_error(char *msg);
int		my_strncmp(const char *a, const char *b, size_t n);
int		my_is_space(int c);
int		my_atoi(const char *s, int *out);
bool	is_valid_map_char(char c);

#endif
