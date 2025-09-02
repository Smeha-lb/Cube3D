#include "../includes/cub3d.h"
#include <string.h>

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
