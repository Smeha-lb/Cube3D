/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:15:26 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/08 14:15:41 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static int	append_buf(char **acc, const char *buf, int n)
{
	char	*tmp;
	int		old;
	int		i;

	old = (int)my_strlen(*acc);
	tmp = (char *)malloc(old + n + 1);
	if (!tmp)
		return (1);
	i = 0;
	while (i < old)
	{
		tmp[i] = (*acc)[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		tmp[old + i] = buf[i];
		i++;
	}
	tmp[old + n] = '\0';
	free(*acc);
	*acc = tmp;
	return (0);
}

static int	count_lines(const char *s)
{
	int i;
	int c;

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

static int	slice_line(const char *src, int start, int end, char **out)
{
	int	len;
	int	i;
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

static int	split_lines(const char *acc, char ***out_lines, int *out_n)
{
	int		count;
	char	**lines;
	int		i;
	int		j;
	int		start;

	count = count_lines(acc);
	lines = (char **)malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (1);
	i = 0;
	j = 0;
	start = 0;
	while (1)
	{
		if (acc[i] == '\n' || acc[i] == '\0')
		{
			if (slice_line(acc, start, i, &lines[j]))
				return (free(lines), 1);
			j++;
			start = i + 1;
			if (acc[i] == '\0')
				break ;
		}
		i++;
	}
	lines[j] = NULL;
	*out_lines = lines;
	*out_n = j;
	return (0);
}

int	read_file_lines(const char *path, char ***out_lines, int *out_n)
{
	int		fd;
	char	buf[1024];
	char	*acc;
	ssize_t	r;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	acc = (char *)malloc(sizeof(char));
	if (!acc)
		return (close(fd), 1);
	acc[0] = '\0';
	r = read(fd, buf, sizeof(buf));
	while (r > 0)
	{
		if (append_buf(&acc, buf, (int)r))
			return (free(acc), close(fd), 1);
		r = read(fd, buf, sizeof(buf));
	}
	close(fd);
	if (r < 0)
		return (free(acc), 1);
	if (split_lines(acc, out_lines, out_n))
		return (free(acc), 1);
	free(acc);
	return (0);
}

int	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines && lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	return (0);
}
