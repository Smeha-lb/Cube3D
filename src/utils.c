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