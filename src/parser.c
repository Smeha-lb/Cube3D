/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:13:55 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/11 15:05:28 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

/* declarations for split helpers */
int			parse_rgb(const char *s, t_color *out);
int			assign_path(char **dst, const char *src);
int			parse_identifier(char *line, t_config *cfg);
int			find_map_start(char **lines, int n);
int			copy_map(char **lines, int start, int n, t_map *map);
int			scan_player(t_map *m);
bool		validate_map_only_chars(char **lines, int start, int end);

static int	parse_identifiers_only(char **lines, int n, t_config *cfg)
{
	int		i;
	int		r;

	i = 0;
	while (i < n)
	{
		r = parse_identifier(lines[i], cfg);
		if (r == 0 || r == 1)
		{
			if (r == 1)
				return (1);
			i++;
			continue ;
		}
		break ;
	}
	return (i);
}

int	parse_cub_file(const char *path, t_config *cfg)
{
	char	**lines;
	int		n;
	int		i;
	int		map_i;

	if (read_file_lines(path, &lines, &n))
		return (1);
	i = parse_identifiers_only(lines, n, cfg);
	if (i < 0)
		return (free_lines(lines), 1);
	map_i = find_map_start(lines, n);
	if (map_i < 0)
		return (free_lines(lines), 1);
	if (!validate_map_only_chars(lines, map_i, n))
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

static void	free_texture_paths(t_config *cfg)
{
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

void	free_config(t_config *cfg)
{
	int	i;

	i = 0;
	while (cfg->map.grid && cfg->map.grid[i])
	{
		free(cfg->map.grid[i]);
		i++;
	}
	free(cfg->map.grid);
	free_texture_paths(cfg);
}
