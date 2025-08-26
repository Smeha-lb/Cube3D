/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <42student@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by 42student        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by 42student       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static int	check_file_exists(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./cub3D <map_file.cub>", 2);
		return (1);
	}
	if (!check_file_extension(argv[1]))
	{
		ft_putendl_fd("Error\nInvalid file extension. Use .cub files only.", 2);
		return (1);
	}
	if (!check_file_exists(argv[1]))
	{
		ft_putendl_fd("Error\nFile does not exist or cannot be opened.", 2);
		return (1);
	}
	init_game(&game);
	if (parse_config(&game, argv[1]) != SUCCESS)
	{
		cleanup_game(&game);
		return (1);
	}
	if (validate_map(&game) != SUCCESS)
	{
		cleanup_game(&game);
		return (1);
	}
	if (load_textures(&game) != SUCCESS)
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_loop(game.mlx_ptr);
	// Ensure all MLX resources are released when the loop ends
	cleanup_game(&game);
	return (0);
}
