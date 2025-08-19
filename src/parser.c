/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_line(t_game *game, char *line)
{
	char	**parts;

	if (!line || line[0] == '\0')
		return (SUCCESS);
	parts = ft_split(line, ' ');
	if (!parts)
		return (ERROR);
	if (ft_strncmp(parts[0], "NO", 2) == 0 || ft_strncmp(parts[0], "SO", 2) == 0
		|| ft_strncmp(parts[0], "WE", 2) == 0 || ft_strncmp(parts[0], "EA", 2) == 0)
	{
		if (parse_textures(game, line) != SUCCESS)
		{
			ft_free_array(parts);
			return (ERROR);
		}
	}
	else if (parts[0][0] == 'F' || parts[0][0] == 'C')
	{
		if (parse_colors(game, line) != SUCCESS)
		{
			ft_free_array(parts);
			return (ERROR);
		}
	}
	else if (parts[0][0] == '1' || parts[0][0] == '0' || parts[0][0] == 'N'
		|| parts[0][0] == 'S' || parts[0][0] == 'E' || parts[0][0] == 'W')
	{
		if (parse_map(game, line) != SUCCESS)
		{
			ft_free_array(parts);
			return (ERROR);
		}
	}
	else
	{
		ft_free_array(parts);
		return (ERROR);
	}
	ft_free_array(parts);
	return (SUCCESS);
}

int	parse_config(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	result = SUCCESS;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(game, line) != SUCCESS)
		{
			result = ERROR;
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	if (result == SUCCESS)
	{
		result = init_mlx(game);
		if (result == SUCCESS)
			result = load_textures(game);
	}
	return (result);
}

int	parse_textures(t_game *game, char *line)
{
	char	**parts;
	int		texture_index;

	parts = ft_split(line, ' ');
	if (!parts || !parts[1])
	{
		ft_free_array(parts);
		return (ERROR);
	}
	if (ft_strncmp(parts[0], "NO", 2) == 0)
		texture_index = NORTH;
	else if (ft_strncmp(parts[0], "SO", 2) == 0)
		texture_index = SOUTH;
	else if (ft_strncmp(parts[0], "WE", 2) == 0)
		texture_index = WEST;
	else if (ft_strncmp(parts[0], "EA", 2) == 0)
		texture_index = EAST;
	else
	{
		ft_free_array(parts);
		return (ERROR);
	}
	game->textures[texture_index].path = ft_strdup(parts[1]);
	if (!game->textures[texture_index].path)
	{
		ft_free_array(parts);
		return (ERROR);
	}
	ft_free_array(parts);
	return (SUCCESS);
}

int	parse_colors(t_game *game, char *line)
{
	char	**parts;
	char	**rgb;
	int		r, g, b;

	parts = ft_split(line, ' ');
	if (!parts || !parts[1])
	{
		ft_free_array(parts);
		return (ERROR);
	}
	rgb = ft_split(parts[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_free_array(parts);
		ft_free_array(rgb);
		return (ERROR);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_array(parts);
		ft_free_array(rgb);
		return (ERROR);
	}
	if (parts[0][0] == 'F')
		game->floor_color = (r << 16) | (g << 8) | b;
	else if (parts[0][0] == 'C')
		game->ceiling_color = (r << 16) | (g << 8) | b;
	ft_free_array(parts);
	ft_free_array(rgb);
	return (SUCCESS);
}

int	parse_map(t_game *game, char *line)
{
	char	**new_map;
	int		i;

	if (!game->map)
	{
		game->map = malloc(sizeof(char *) * 2);
		if (!game->map)
			return (ERROR);
		game->map[0] = ft_strdup(line);
		game->map[1] = NULL;
		game->map_height = 1;
	}
	else
	{
		new_map = malloc(sizeof(char *) * (game->map_height + 2));
		if (!new_map)
			return (ERROR);
		i = 0;
		while (i < game->map_height)
		{
			new_map[i] = game->map[i];
			i++;
		}
		new_map[i] = ft_strdup(line);
		new_map[i + 1] = NULL;
		free(game->map);
		game->map = new_map;
		game->map_height++;
	}
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	char	buffer[2];
	char	*line;
	int		bytes_read;

	line = NULL;
	while ((bytes_read = read(fd, buffer, 1)) > 0)
	{
		buffer[1] = '\0';
		if (buffer[0] == '\n')
			break ;
		if (!line)
			line = ft_strdup(buffer);
		else
		{
			char	*temp = line;
			int		len = ft_strlen(temp);
			line = malloc(len + 2);
			if (!line)
			{
				free(temp);
				return (NULL);
			}
			ft_strcpy(line, temp);
			line[len] = buffer[0];
			line[len + 1] = '\0';
			free(temp);
		}
	}
	return (line);
}
