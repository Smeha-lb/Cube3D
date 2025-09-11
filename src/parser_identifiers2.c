/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifiers2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:55:51 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 15:01:14 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_identifier(char *line, t_config *cfg)
{
	int	res;

	res = parse_texture_keys(line, cfg);
	if (res != 2)
		return (res);
	if (my_strncmp(line, "F ", 2) == 0)
		return (parse_rgb(line + 2, &cfg->floor));
	if (my_strncmp(line, "C ", 2) == 0)
		return (parse_rgb(line + 2, &cfg->ceiling));
	return (2);
}
