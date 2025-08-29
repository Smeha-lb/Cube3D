#include "../includes/cub3d.h"

int	on_destroy(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	app->running = 0;
	app_cleanup(app);
	exit(0);
	return (0);
}

int	on_key_press(int keycode, void *param)
{
	t_app *a;

	a = (t_app *)param;
	if (keycode == 65307)
		on_destroy(param);
	if (keycode == 'w' || keycode == 'W')
		a->keys.w = 1;
	if (keycode == 's' || keycode == 'S')
		a->keys.s = 1;
	if (keycode == 'a' || keycode == 'A')
		a->keys.a = 1;
	if (keycode == 'd' || keycode == 'D')
		a->keys.d = 1;
	if (keycode == 65361)
		a->keys.left = 1;
	if (keycode == 65363)
		a->keys.right = 1;
	if (keycode == 'e' || keycode == 'E')
		toggle_door_in_front(a);
	return (0);
}

int	on_key_release(int keycode, void *param)
{
	t_app *a;

	a = (t_app *)param;
	if (keycode == 'w' || keycode == 'W')
		a->keys.w = 0;
	if (keycode == 's' || keycode == 'S')
		a->keys.s = 0;
	if (keycode == 'a' || keycode == 'A')
		a->keys.a = 0;
	if (keycode == 'd' || keycode == 'D')
		a->keys.d = 0;
	if (keycode == 65361)
		a->keys.left = 0;
	if (keycode == 65363)
		a->keys.right = 0;
	return (0);
}
