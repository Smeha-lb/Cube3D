/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamaha <csamaha@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:17 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/09 13:08:24 by csamaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

size_t	my_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	my_strncmp(const char *a, const char *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && a[i] && b[i])
	{
		if ((unsigned char)a[i] != (unsigned char)b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

char	*my_strdup(const char *s)
{
	size_t	len;
	char	*p;
	size_t	i;

	len = my_strlen(s);
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}

int	my_is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	if (c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	my_atoi(const char *s, int *out)
{
	long	v;
	int		sign;

	v = 0;
	sign = 1;
	while (*s && my_is_space(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		v = v * 10 + (*s - '0');
		s++;
	}
	v = v * sign;
	*out = (int)v;
	return (0);
}
