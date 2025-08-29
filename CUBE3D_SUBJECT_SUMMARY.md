## cub3D – Essential Requirements Summary

Source: `Cube3D.subject.txt`

### Goal
Build a raycasting engine (Wolfenstein 3D style) using MiniLibX that renders a 3D view of a 2D map from a first-person perspective.

### Mandatory Specifications
- Program name: `cub3D`
- Language: C, follow 42 Norm, no crashes, no leaks
- Makefile: `all`, `clean`, `fclean`, `re`, `bonus` using `cc` with `-Wall -Wextra -Werror`
- Libraries allowed: libft, math (`-lm`), `gettimeofday`, MiniLibX
- Input: first argument is a `.cub` scene file

### Scene File Format (.cub)
Order among elements (except map) is free; blank lines allowed between elements; map is last and must be parsed exactly as-is (spaces significant).

Required identifiers before the map:
- `NO path_to_north_texture.xpm`
- `SO path_to_south_texture.xpm`
- `WE path_to_west_texture.xpm`
- `EA path_to_east_texture.xpm`
- `F R,G,B` (0–255)
- `C R,G,B` (0–255)

Map constraints:
- Characters: `0` empty, `1` wall, one of `N/S/E/W` is the single player start and orientation
- Map must be fully enclosed (surrounded by `1`); no leaks
- Map is last section; spaces are part of map

### Program Behavior
- Display a window showing the scene; use MiniLibX images
- Apply different wall textures based on wall face: North, South, West, East
- Set distinct floor and ceiling colors
- Controls:
  - Arrow Left/Right: rotate view
  - W/A/S/D: move
  - ESC: exit cleanly
  - Window close button: exit cleanly

### Error Handling
- On any misconfiguration: print `Error\n` followed by an explicit message; exit cleanly

### Cleanup
- Free all allocated memory; destroy MLX images/window; avoid leaks

### Bonus (only evaluated if mandatory is perfect)
- Collisions
- Minimap
- Doors (open/close)
- Animated sprites
- Mouse to rotate

### Implementation Notes
- Prefer images over per-pixel window writes for performance
- Keep window responsive; rely on MLX loop and hooks
- Raycasting: per-column ray cast with DDA, perpendicular distance, texture sampling per column

### Deliverables
- All sources in repo; subject to deepthought/peer-eval; ensure names are correct


