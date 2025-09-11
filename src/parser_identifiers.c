/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:55:51 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/11 15:00:29 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	try_assign(char *line, const char *pfx, char **dst)
{
	int	len;

	len = (int)my_strlen(pfx);
	if (my_strncmp(line, pfx, (size_t)len) == 0)
		return (assign_path(dst, line + len));
	return (2);
}

static int	parse_component(const char *s, int *i, int *dst)
{
	int	j;

	j = *i;
	if (my_atoi(s + j, dst))
		return (1);
	while (s[j] && s[j] != ',')
		j++;
	*i = j;
	return (0);
}

int	parse_rgb(const char *s, t_color *out)
{
	int	i;

	i = 0;
	if (parse_component(s, &i, &out->r))
		return (1);
	if (s[i] != ',')
		return (1);
	i++;
	if (parse_component(s, &i, &out->g))
		return (1);
	if (s[i] != ',')
		return (1);
	i++;
	if (parse_component(s, &i, &out->b))
		return (1);
	if (out->r < 0 || out->r > 255)
		return (1);
	if (out->g < 0 || out->g > 255)
		return (1);
	if (out->b < 0 || out->b > 255)
		return (1);
	out->argb = (0xFF << 24) | (out->r << 16)
		| (out->g << 8) | out->b;
	return (0);
}

int	assign_path(char **dst, const char *src)
{
	if (*dst)
		return (1);
	*dst = my_strdup(src);
	return (*dst == NULL);
}

int	parse_texture_keys(char *line, t_config *cfg)
{
	int	res;

	res = try_assign(line, "NO ", &cfg->tex_no.path);
	if (res != 2)
		return (res);
	res = try_assign(line, "SO ", &cfg->tex_so.path);
	if (res != 2)
		return (res);
	res = try_assign(line, "WE ", &cfg->tex_we.path);
	if (res != 2)
		return (res);
	res = try_assign(line, "EA ", &cfg->tex_ea.path);
	if (res != 2)
		return (res);
	res = try_assign(line, "DO ", &cfg->tex_door.path);
	if (res != 2)
		return (res);
	res = try_assign(line, "TO ", &cfg->tex_torch.path);
	return (res);
}
