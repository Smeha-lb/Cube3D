/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:34:28 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:35:33 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	slice_line(const char *src, int start, int end, char **out)
{
	int		len;
	int		i;
	char	*s;

	len = end - start;
	s = (char *)malloc(len + 1);
	if (!s)
		return (1);
	i = 0;
	while (i < len)
	{
		s[i] = src[start + i];
		i++;
	}
	s[len] = '\0';
	*out = s;
	return (0);
}

static int	count_lines_local(const char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 1;
	while (s[i])
	{
		if (s[i] == '\n')
			c++;
		i++;
	}
	return (c);
}

static int	do_split_fill(const char *acc, char **lines)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (1)
	{
		if (acc[i] == '\n' || acc[i] == '\0')
		{
			if (slice_line(acc, start, i, &lines[j]))
				return (1);
			j++;
			start = i + 1;
			if (acc[i] == '\0')
				break ;
		}
		i++;
	}
	lines[j] = NULL;
	return (0);
}

int	split_lines(const char *acc, char ***out_lines, int *out_n)
{
	int		count;
	char	**lines;

	count = count_lines_local(acc);
	lines = (char **)malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (1);
	if (do_split_fill(acc, lines))
		return (free(lines), 1);
	*out_lines = lines;
	*out_n = count;
	return (0);
}
