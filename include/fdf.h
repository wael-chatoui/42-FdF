/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:27:23 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 10:23:28 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080
# define MENU_WIDTH 250

# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Key codes for Linux */
# define KEY_ESC 65307
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_Q 113
# define KEY_W 119
# define KEY_E 101
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R 114
# define KEY_P 112
# define KEY_I 105
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define MOUSE_MIDDLE 2
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

/* Colors */
# define COLOR_WHITE 0xFFFFFF
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_PURPLE 0xFF00FF
# define COLOR_CYAN 0x00FFFF
# define COLOR_BACKGROUND 0x222222
# define COLOR_MENU_BG 0x2D2D30
# define COLOR_TEXT 0xECECEC

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_point;

typedef struct s_cam
{
	int		zoom;
	double	alpha;
	double	beta;
	double	gamma;
	float	z_scale;
	int		x_offset;
	int		y_offset;
	int		projection;
}	t_cam;

typedef struct s_mouse
{
	int		is_pressed;
	int		x;
	int		y;
	int		prev_x;
	int		prev_y;
}	t_mouse;

typedef struct s_map
{
	int		width;
	int		height;
	int		z_min;
	int		z_max;
	int		has_colors;
	t_point	**points;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	*map;
	t_cam	*cam;
	t_mouse	*mouse;
}	t_fdf;

/* Parsing functions */
void	parse_map(char *file, t_fdf *fdf);
void	read_map(char *file, t_fdf *fdf);
int		get_map_width(char *line);
int		get_map_height(char *file);
void	fill_map(char *file, t_fdf *fdf);
int		get_color(char *str);
/* ft_atoi_base is already declared in libft.h */

/* Initialization functions */
void	init_fdf(t_fdf *fdf);
void	init_cam(t_fdf *fdf);
void	init_mouse(t_fdf *fdf);

/* Drawing functions */
void	draw(t_fdf *fdf);
void	draw_line(t_fdf *fdf, t_point p1, t_point p2);
void	put_pixel(t_fdf *fdf, int x, int y, int color);
void	clear_image(t_fdf *fdf);
void	draw_menu(t_fdf *fdf);

/* Transformation functions */
t_point	project(t_point p, t_fdf *fdf);
void	rotate_x(int *y, int *z, double alpha);
void	rotate_y(int *x, int *z, double beta);
void	rotate_z(int *x, int *y, double gamma);
void	iso_project(int *x, int *y, int z);
t_point	transform_point(t_point p, t_fdf *fdf);

/* Color functions */
int		get_gradient(int start, int end, double percent);
int		get_default_color(int z, t_fdf *fdf);
double	get_percent(int start, int end, int current);

/* Hook functions */
int		key_press(int key, t_fdf *fdf);
int		mouse_press(int button, int x, int y, t_fdf *fdf);
int		mouse_release(int button, int x, int y, t_fdf *fdf);
int		mouse_move(int x, int y, t_fdf *fdf);
int		close_window(t_fdf *fdf);

/* Utility functions */
void	ft_error(char *msg);
void	free_map(t_fdf *fdf);
/* ft_abs is already declared in libft.h */
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	reset_cam(t_fdf *fdf);

#endif
