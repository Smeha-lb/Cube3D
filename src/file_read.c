/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:38:50 by csamaha           #+#    #+#             */
/*   Updated: 2025/09/09 16:39:16 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static void	copy_bytes(char *dst, const char *src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dst[i] = src[i];
		i++;
	}
}

static int	append_buf(char **acc, const char *buf, int n)
{
	char	*tmp;
	int		old;

	old = (int)my_strlen(*acc);
	tmp = (char *)malloc(old + n + 1);
	if (!tmp)
		return (1);
	copy_bytes(tmp, *acc, old);
	copy_bytes(tmp + old, buf, n);
	tmp[old + n] = '\0';
	free(*acc);
	*acc = tmp;
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
	return (free(acc), 0);
}
