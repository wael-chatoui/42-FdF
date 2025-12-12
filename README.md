# FdF

FdF (Fil de Fer) — a 3D wireframe viewer project from 42 school. This repository contains a compact implementation that parses height-maps (.fdf files) and renders them as a rotatable/zoomable wireframe using the MiniLibX/MLX windowing library.

**Status:** Near completion — README is a template. Update controls and runtime flags as you finish the project.

**Features:**
- Parse space-separated height maps from `test_maps/`.
- Render a 3D wireframe projection of the map.
- Basic interactions: panning, zoom, rotate, and exit (see Controls).

**Requirements**
- Linux (X11)
- `gcc`, `make`
- X11 development libraries (e.g. `libx11-dev`, `libxext-dev`)
- `minilibx-linux` (included in this repository)

If you prefer a different MLX implementation (like MLX42), adapt the Makefile accordingly.

Build
```
# From project root
make

# If there are separate Makefiles for submodules you can also:
cd minilibx-linux && make && cd ..
```

Run
```
./fdf test_maps/42.fdf
```
Replace `test_maps/42.fdf` with any other `.fdf` file in `test_maps/` or your own map file.

Usage (example)
- `./fdf path/to/map.fdf`
- Optional flags (if implemented): `scale`, `height_scale` — check your program's argument parsing.

Controls
- `ESC` : Quit
- Mouse scroll or `+` / `-` : Zoom in/out (if implemented)
- Arrow keys : Pan the view
- Mouse drag or `Q`/`E` : Rotate the wireframe (implementation-dependent)

(Note) Exact controls depend on your final key/mouse handling. Update this section to match your implementation.

Map format
- The `.fdf` map format is a whitespace-separated grid of integers representing heights.
Example (3x3 grid):
```
0 0 0
0 1 0
0 0 0
```

Project layout
- `src/` — source files for the FdF program (`main.c`, `draw.c`, parsing, etc.)
- `include/` — project headers (`fdf.h`)
- `minilibx-linux/` — included MiniLibX library (X11)
- `test_maps/` — example `.fdf` maps to try
- `ft_printf/`, `get_next_line/` — helper libraries used by the project

Contributing
- This repository is a personal project for 42 school. If you want to contribute, open an issue or a PR with a short description of your change.

License & Author
- Author: Your Name (replace this placeholder)
- License: add a LICENSE file or update this section to reflect the chosen license.

Tips / Troubleshooting
- If the build fails with MLX errors, ensure X11 dev packages are installed (`sudo apt install libx11-dev libxext-dev libbsd-dev`).
- If the binary cannot open a window, check your display/X11 configuration and that your environment supports OpenGL/X11 on Linux.

Update this README with final controls, build flags, and any runtime options once the project is finished.
# 42-FdF
