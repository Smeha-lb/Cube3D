#include "../includes/cub3d.h"
#include <string.h>

static int	print_error(const char *msg)
{
	write(2, T_COL_RED "Error\n" T_COL_RESET, 5 + 6 + 4);
	if (msg)
		write(2, msg, (int)strlen(msg));
	write(2, "\n", 1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_app	app;

	(void)argv;
	if (argc != 2)
		return (print_error("Usage: ./cub3D <map.cub>"));
	if (app_init(&app, argv[1]) != 0)
		return (print_error("Initialization failed"));
	mlx_loop(app.mlx);
	app_cleanup(&app);
	return (0);
}
