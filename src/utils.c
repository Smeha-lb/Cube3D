/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:06 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/08 14:10:09 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_map_char(char c)
{
	int		i;
	char	*valid_charset;

	i = 0;
	valid_charset = VALID_MAP_CHARS;
	while (i < (int)my_strlen(valid_charset))
	{
		if (c == valid_charset[i])
			return (true);
		i++;
	}
	return (false);
}
