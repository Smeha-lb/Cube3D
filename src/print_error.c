/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:59:01 by moabdels          #+#    #+#             */
/*   Updated: 2025/09/02 16:35:44 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_puterr(char *s)
{
	write(STDERR_FILENO, s, (int)my_strlen(s));
}

int	print_error(char *msg)
{
	ft_puterr(T_COL_RED"Error: "T_COL_RESET);
	if (msg)
		ft_puterr(msg);
	return (1);
}
