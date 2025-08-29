## MiniLibX Quick Reference (42)

Reference used: [MiniLibX docs](https://harm-smits.github.io/42docs/libs/minilibx)

### Overview
MiniLibX (MLX) is a thin wrapper over X11/Cocoa for simple graphics. Typical flow: init → create window → create images → draw to image buffer → put image to window → process events in loop → clean up.

### Build & Link (Linux)
- Compile flags: `-Wall -Wextra -Werror`
- Include: `-Iminilibx-linux`
- Link: `-Lminilibx-linux -lmlx -lXext -lX11 -lm -lz`
- Build MLX first: `make -C minilibx-linux`

### Initialization & Teardown
- `void *mlx_init(void);`
- `void *mlx_new_window(void *mlx, int w, int h, char *title);`
- `int mlx_destroy_window(void *mlx, void *win);`
- `void *mlx_new_image(void *mlx, int w, int h);`
- `char *mlx_get_data_addr(void *img, int *bpp, int *line_len, int *endian);`
- `int mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y);`
- `int mlx_destroy_image(void *mlx, void *img);`
- Linux extra cleanup: `void mlx_destroy_display(void *mlx); free(mlx);`

### Event Loop & Hooks
- Main loop: `int mlx_loop(void *mlx);`
- Per-frame function: `int mlx_loop_hook(void *mlx, int (*f)(void *), void *param);`
- Generic hook: `int mlx_hook(void *win, int event, int mask, int (*f)(), void *param);`

Common X11 event codes and masks (Linux):
- KeyPress: event 2, mask `1L<<0`
- KeyRelease: event 3, mask `1L<<1`
- ButtonPress: event 4, mask `1L<<2`
- ButtonRelease: event 5, mask `1L<<3`
- MotionNotify: event 6, mask `1L<<6`
- Expose: event 12, mask `1L<<15`
- DestroyNotify: event 17, mask `0` or `1L<<17` via StructureNotifyMask

Convenience hooks:
- `int mlx_key_hook(void *win, int (*f)(int keycode, void *), void *param);` (KeyPress only)
- `int mlx_mouse_hook(void *win, int (*f)(int button, int x, int y, void *), void *param);`

Handler signatures (Linux):
- Key: `int handler(int keycode, void *param)`
- Mouse press: `int handler(int button, int x, int y, void *param)`
- Motion: `int handler(int x, int y, void *param)`
- Destroy: `int handler(void *param)`

### Images & Pixels
- Create image: `mlx_new_image`
- Access buffer: `mlx_get_data_addr` returns:
  - `bpp` (bits per pixel)
  - `line_len` (bytes per row)
  - `endian` (0 little-endian)
- Put to window every frame: `mlx_put_image_to_window`
- Per-pixel write is done by computing `addr + y * line_len + x * (bpp/8)` and storing a 32-bit color.
- `mlx_pixel_put` exists but is slow. Prefer image buffers.

### XPM Textures
- `void *mlx_xpm_file_to_image(void *mlx, char *path, int *w, int *h);`
- Then call `mlx_get_data_addr` to sample pixels.

### Colors
- Use 0xAARRGGBB or 0x00RRGGBB in a 32-bit word; how it appears in memory depends on endianness/bpp.
- If unsure, write via 32-bit store to the image buffer as returned by `mlx_get_data_addr`.
- Floor/Ceiling colors typically stored as packed 24-bit RGB.

### Strings & UI
- `int mlx_string_put(void *mlx, void *win, int x, int y, int color, char *str);`
- Basic debugging overlay or HUD text.

### Timing & Sync
- Main loop cadence is event driven; for fixed-rate updates, call your update in `mlx_loop_hook`.
- `mlx_do_sync(mlx)` can force a flush on some platforms; usually not required on Linux when using images + loop.

### Typical Pattern (Linux)
```c
mlx = mlx_init();
win = mlx_new_window(mlx, W, H, "title");
img = mlx_new_image(mlx, W, H);
addr = mlx_get_data_addr(img, &bpp, &line, &endian);
mlx_hook(win, 17, 0, on_destroy, ctx);
mlx_hook(win, 2, 1L<<0, on_key_press, ctx);
mlx_hook(win, 3, 1L<<1, on_key_release, ctx);
mlx_loop_hook(mlx, on_frame, ctx);
mlx_loop(mlx);
// cleanup: destroy image/window, mlx_destroy_display(mlx), free(mlx)
```

### Common Pitfalls
- Not using images (slow `mlx_pixel_put` in loops).
- Wrong event masks on Linux → handlers never fire. Use the bitmasks above.
- Forgetting Linux-specific cleanup: `mlx_destroy_display` and `free(mlx)`.
- Writing past image bounds; always clamp `0 <= x < width`, `0 <= y < height`.
- Assuming color byte order; always write via 32-bit store to the buffer pointer.
- Recreating images every frame; create once, reuse, and blit each frame.

### Prototypes (selection)
```c
void *mlx_init();
void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
int   mlx_destroy_window(void *mlx_ptr, void *win_ptr);
void *mlx_new_image(void *mlx_ptr, int width, int height);
char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
int   mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
int   mlx_destroy_image(void *mlx_ptr, void *img_ptr);
void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
int   mlx_loop(void *mlx_ptr);
int   mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param);
int   mlx_hook(void *win_ptr, int x_event, int x_mask, int (*f)(), void *param);
int   mlx_key_hook(void *win_ptr, int (*f)(), void *param);
int   mlx_mouse_hook(void *win_ptr, int (*f)(), void *param);
```

### Notes for 42 cub3D
- Prefer `mlx_loop_hook` for per-frame updates (movement, raycasting, render).
- Hook KeyPress/KeyRelease for movement state; apply movement in the loop.
- Load four wall textures via `mlx_xpm_file_to_image` and sample in vertical wall slices.


