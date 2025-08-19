/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.05
# define MOUSE_SENSITIVITY 0.0025
# define FOV 0.8

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_M 109
# define KEY_SHIFT_L 65505
# define KEY_SHIFT_R 65506

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define SUCCESS 0
# define ERROR 1

# define SPRINT_MULTIPLIER 2.0

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit_side;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
} t_ray;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*path;
} t_texture;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	player;
	char		**map;
	int			map_width;
	int			map_height;
	t_texture	textures[4];
	int			floor_color;
	int			ceiling_color;
	int			keys[65536];
	void		*screen_img;
	char		*screen_addr;
	int			screen_bits_per_pixel;
	int			screen_line_length;
	int			screen_endian;
	int			mouse_prev_x;
	int			mouse_initialized;
	int			warping_mouse;
	int			mouse_captured;
} t_game;

// Main functions
int		main(int argc, char **argv);
void	init_game(t_game *game);
void	cleanup_game(t_game *game);
int		init_mlx(t_game *game);

// Parser functions
int		parse_config(t_game *game, char *filename);
int		parse_textures(t_game *game, char *line);
int		parse_colors(t_game *game, char *line);
int		parse_map(t_game *game, char *line);

// Map validation functions
int		validate_map(t_game *game);
int		check_wall_closure(t_game *game);
int		find_player_spawn(t_game *game, int y, int x);

// Raycasting functions
void	cast_rays(t_game *game);
void	init_ray(t_ray *ray, t_game *game, int x);
void	perform_dda(t_ray *ray, t_game *game);
void	calculate_wall_height(t_ray *ray, t_game *game);

// Player functions
void	init_player(t_game *game);
void	move_player(t_game *game);
void	rotate_player(t_game *game, double angle);

// Controls functions
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_close(t_game *game);
void	handle_movement(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

// Rendering functions
int		render_frame(t_game *game);
void	render_walls(t_game *game, t_ray *ray, int x);
void	render_walls_to_buffer(t_game *game, t_ray *ray, int x);
void	render_floor_ceiling(t_game *game);
void	render_walls_to_image(t_game *game);
void	draw_vertical_line(t_game *game, int x, int start, int end, int color);

// Mouse functions
int		handle_mouse_move(int x, int y, t_game *game);
int		process_mouse_look(t_game *game);
int		handle_enter_window(int x, int y, t_game *game);
int		handle_leave_window(int x, int y, t_game *game);

// Texture functions
int		load_textures(t_game *game);
void	apply_texture(t_game *game, t_ray *ray, int x, int wall_height);
int		get_texture_x(t_ray *ray, t_texture *texture);
int		get_wall_texture_index(t_ray *ray);
int		get_texture_color(t_texture *texture, int x, int y);

// Utility functions
int		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
int		ft_atoi(const char *str);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putendl_fd(const char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
void		ft_free_array(char **array);
void		ft_strcpy(char *dest, const char *src);
void		ft_strcat(char *dest, const char *src);
char		*get_next_line(int fd);

// Error handling
void		error_exit(t_game *game, const char *message);
void		cleanup_resources(t_game *game);

#endif
