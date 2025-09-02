#include "../includes/cub3d.h"

static int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'T')
		return (1);
	return (0);
}

static int	cell_at(t_map *m, int x, int y)
{
	if (y < 0 || y >= m->height)
		return (' ');
	if (x < 0)
		return (' ');
	if (x >= (int)my_strlen(m->grid[y]))
		return (' ');
	return (m->grid[y][x]);
}

int		map_is_wall(t_map *map, int x, int y)
{
	char c;

	c = cell_at(map, x, y);
	if (c == '1' || c == 'D')
		return (1);
	return (0);
}

int		validate_map_closed(t_map *m)
{
	int y;
	int x;
	char c;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (m->grid[y][x])
		{
			c = m->grid[y][x];
			if (is_walkable(c) && (cell_at(m, x+1, y) == ' '
				|| cell_at(m, x-1, y) == ' '
				|| cell_at(m, x, y+1) == ' '
				|| cell_at(m, x, y-1) == ' '))
			{
				printf("y=%d x=%d", y+9, x);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
