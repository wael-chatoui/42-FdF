/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:25:10 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 22:24:54 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx-linux/mlx.h"

static void	init_bresenham(
	t_point *p1, t_point *p2, t_point *delta, t_point *sign
)
{
	delta->x = ft_abs(p2->x - p1->x);
	delta->y = ft_abs(p2->y - p1->y);
	if (p1->x < p2->x)
		sign->x = 1;
	else
		sign->x = -1;
	if (p1->y < p2->y)
		sign->y = 1;
	else
		sign->y = -1;
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
	current_distance = ft_max(ft_abs(current.x - p1.x), \
	ft_abs(current.y - p1.y));
	if (distance == 0)
		percent = 1.0;
	else
		percent = (double)current_distance / distance;
	return (get_gradient(color1, color2, percent));
}

static void	bresenham_step(
	int error[2],
	t_point *delta,
	t_point *current,
	t_point *sign
)
{
	if (error[1] > -delta->y)
	{
		error[0] -= delta->y;
		current->x += sign->x;
	}
	if (error[1] < delta->x)
	{
		error[0] += delta->x;
		current->y += sign->y;
	}
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
		put_pixel(fdf, current.x, current.y,
			get_line_color(p1, p2, current, fdf));
		error[1] = error[0] * 2;
		bresenham_step(error, &delta, &current, &sign);
	}
	put_pixel(fdf, p2.x, p2.y,
		get_line_color(p1, p2, p2, fdf));
}

void	draw_grid(t_fdf *fdf)
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
				draw_line(fdf, fdf->map->points[y][x], \
					fdf->map->points[y][x + 1]);
			if (y < fdf->map->height - 1)
				draw_line(fdf, fdf->map->points[y][x], \
					fdf->map->points[y + 1][x]);
			x++;
		}
		y++;
	}
}
