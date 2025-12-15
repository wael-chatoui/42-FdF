/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:25:10 by wael              #+#    #+#             */
/*   Updated: 2025/12/14 17:54:53 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx-linux/mlx.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = fdf->img.addr + (y * fdf->img.line_len + x * (fdf->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	clear_image(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(fdf, x, y, COLOR_BACKGROUND);
			x++;
		}
		y++;
	}
}

static void	init_bresenham(t_point *p1, t_point *p2, t_point *delta, t_point *sign)
{
	delta->x = ft_abs(p2->x - p1->x);
	delta->y = ft_abs(p2->y - p1->y);
	sign->x = p1->x < p2->x ? 1 : -1;
	sign->y = p1->y < p2->y ? 1 : -1;
}

static int	get_line_color(t_point p1, t_point p2, t_point current, t_fdf *fdf)
{
	int		color1;
	int		color2;
	double	percent;
	int		distance;
	int		current_distance;

	color1 = p1.color;
	color2 = p2.color;
	if (color1 == -1)
		color1 = get_default_color(p1.z, fdf);
	if (color2 == -1)
		color2 = get_default_color(p2.z, fdf);
	distance = ft_max(ft_abs(p2.x - p1.x), ft_abs(p2.y - p1.y));
	current_distance = ft_max(ft_abs(current.x - p1.x), ft_abs(current.y - p1.y));
	if (distance == 0)
		percent = 1.0;
	else
		percent = (double)current_distance / distance;
	return (get_gradient(color1, color2, percent));
}

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	delta;
	t_point	sign;
	t_point	current;
	int		error[2];

	p1 = transform_point(p1, fdf);
	p2 = transform_point(p2, fdf);
	init_bresenham(&p1, &p2, &delta, &sign);
	error[0] = delta.x - delta.y;
	current = p1;
	while (current.x != p2.x || current.y != p2.y)
	{
		put_pixel(fdf, current.x, current.y, get_line_color(p1, p2, current, fdf));
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
		{
			error[0] -= delta.y;
			current.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			current.y += sign.y;
		}
	}
	put_pixel(fdf, p2.x, p2.y, get_line_color(p1, p2, p2, fdf));
}

static void	draw_grid(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_line(fdf, fdf->map->points[y][x], fdf->map->points[y][x + 1]);
			if (y < fdf->map->height - 1)
				draw_line(fdf, fdf->map->points[y][x], fdf->map->points[y + 1][x]);
			x++;
		}
		y++;
	}
}

void	draw(t_fdf *fdf)
{
	clear_image(fdf);
	draw_grid(fdf);
	draw_menu(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
