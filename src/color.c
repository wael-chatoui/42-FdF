/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:00:00 by wael              #+#    #+#             */
/*   Updated: 2025/12/14 17:54:23 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (placement / distance);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_gradient(int start, int end, double percent)
{
	int	red;
	int	green;
	int	blue;

	if (start == end)
		return (start);
	red = get_light((start >> 16) & 0xFF, (end >> 16) & 0xFF, percent);
	green = get_light((start >> 8) & 0xFF, (end >> 8) & 0xFF, percent);
	blue = get_light(start & 0xFF, end & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

int	get_default_color(int z, t_fdf *fdf)
{
	double	percent;

	if (fdf->map->z_max == fdf->map->z_min)
		return (COLOR_WHITE);
	percent = get_percent(fdf->map->z_min, fdf->map->z_max, z);
	if (percent < 0.2)
		return (get_gradient(0x0000FF, 0x00FFFF, percent * 5));
	else if (percent < 0.4)
		return (get_gradient(0x00FFFF, 0x00FF00, (percent - 0.2) * 5));
	else if (percent < 0.6)
		return (get_gradient(0x00FF00, 0xFFFF00, (percent - 0.4) * 5));
	else if (percent < 0.8)
		return (get_gradient(0xFFFF00, 0xFF8800, (percent - 0.6) * 5));
	else
		return (get_gradient(0xFF8800, 0xFF0000, (percent - 0.8) * 5));
}
