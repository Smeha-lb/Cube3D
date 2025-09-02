#include "../includes/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static int	parse_rgb(const char *s, t_color *out)
{
	int i;

	i = 0;
	if (my_atoi(s + i, &out->r))
		return (1);
	while (s[i] && s[i] != ',')
		i++;
	if (s[i] != ',')
		return (1);
	i++;
	if (my_atoi(s + i, &out->g))
		return (1);
	while (s[i] && s[i] != ',')
		i++;
	if (s[i] != ',')
		return (1);
	i++;
	if (my_atoi(s + i, &out->b))
		return (1);
	if (out->r < 0 || out->r > 255)
		return (1);
	if (out->g < 0 || out->g > 255)
		return (1);
	if (out->b < 0 || out->b > 255)
		return (1);
	out->argb = (0xFF << 24) | (out->r << 16) | (out->g << 8) | out->b;
	return (0);
}

static int	assign_path(char **dst, const char *src)
{
	if (*dst)
		return (1);
	*dst = my_strdup(src);
	return (*dst == NULL);
}

static int	parse_identifier(char *line, t_config *cfg)
{
	if (my_strncmp(line, "NO ", 3) == 0)
		return (assign_path(&cfg->tex_no.path, line + 3));
	if (my_strncmp(line, "SO ", 3) == 0)
		return (assign_path(&cfg->tex_so.path, line + 3));
	if (my_strncmp(line, "WE ", 3) == 0)
		return (assign_path(&cfg->tex_we.path, line + 3));
	if (my_strncmp(line, "EA ", 3) == 0)
		return (assign_path(&cfg->tex_ea.path, line + 3));
	if (my_strncmp(line, "DO ", 3) == 0)
		return (assign_path(&cfg->tex_door.path, line + 3));
	if (my_strncmp(line, "TO ", 3) == 0)
		return (assign_path(&cfg->tex_torch.path, line + 3));
	if (my_strncmp(line, "F ", 2) == 0)
		return (parse_rgb(line + 2, &cfg->floor));
	if (my_strncmp(line, "C ", 2) == 0)
		return (parse_rgb(line + 2, &cfg->ceiling));
	return (2);
}

static int	find_map_start(char **lines, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (lines[i][0] == '1' || lines[i][0] == '0' || lines[i][0] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

static int	copy_map(char **lines, int start, int n, t_map *map)
{
	int i;
	int h;
	int w;

	h = n - start;
	map->grid = (char **)malloc(sizeof(char *) * (h + 1));
	if (!map->grid)
		return (1);
	map->height = h;
	map->width = 0;
	i = 0;
	while (i < h)
	{
		map->grid[i] = my_strdup(lines[start + i]);
		if (!map->grid[i])
			return (1);
		w = (int)my_strlen(map->grid[i]);
		if (w > map->width)
			map->width = w;
		i++;
	}
	map->grid[h] = NULL;
	return (0);
}

static int	scan_player(t_map *m)
{
	int y;
	int x;
	int found;

	y = 0;
	found = 0;
	while (y < m->height)
	{
		x = 0;
		while (m->grid[y][x])
		{
			if (m->grid[y][x] == 'N' || m->grid[y][x] == 'S' || m->grid[y][x] == 'E' || m->grid[y][x] == 'W')
			{
				m->player_x = x;
				m->player_y = y;
				m->player_dir = m->grid[y][x];
				found++;
			}
			x++;
		}
		y++;
	}
	if (found == 1)
		return (0);
	return (1);
}

// TODO: this needs to be moved to before main, and
int		parse_cub_file(const char *path, t_config *cfg)
{
	char	**lines;
	int		n;
	int		i;
	int		map_i;
	int		r;

	if (read_file_lines(path, &lines, &n))
		return (1);
	i = 0;
	while (i < n)
	{
		r = parse_identifier(lines[i], cfg);
		if (r == 0 || r == 1)
		{
			if (r == 1)
				return (free_lines(lines), 1);
			i++;
			continue ;
		}
		break ;
	}
	map_i = find_map_start(lines, n);
	if (map_i < 0)
		return (free_lines(lines), 1);
	if (copy_map(lines, map_i, n, &cfg->map))
		return (free_lines(lines), 1);
	if (scan_player(&cfg->map))
		return (free_lines(lines), 1);
	if (validate_map_closed(&cfg->map))
		return (free_lines(lines), 1);
	free_lines(lines);
	return (0);
}

void	free_config(t_config *cfg)
{
	int i;

	i = 0;
	while (cfg->map.grid && cfg->map.grid[i])
	{
		free(cfg->map.grid[i]);
		i++;
	}
	free(cfg->map.grid);
	if (cfg->tex_no.path)
		free(cfg->tex_no.path);
	if (cfg->tex_so.path)
		free(cfg->tex_so.path);
	if (cfg->tex_we.path)
		free(cfg->tex_we.path);
	if (cfg->tex_ea.path)
		free(cfg->tex_ea.path);
	if (cfg->tex_door.path)
		free(cfg->tex_door.path);
	if (cfg->tex_torch.path)
		free(cfg->tex_torch.path);
	cfg->tex_no.path = NULL;
	cfg->tex_so.path = NULL;
	cfg->tex_we.path = NULL;
	cfg->tex_ea.path = NULL;
	cfg->tex_door.path = NULL;
	cfg->tex_torch.path = NULL;
	if (cfg->sprites)
		free(cfg->sprites);
	cfg->sprites = NULL;
	cfg->num_sprites = 0;
}


