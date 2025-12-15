/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:00:00 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 22:42:31 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_project(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

//p.y = (int)(prev_y * cos(a) + prev_z * sin(a));
t_point	transform_point(t_point p, t_fdf *fdf)
{
	double	prev_y;
	double	prev_z;
	double	a;

	p.x -= fdf->map->width / 2;
	p.y -= fdf->map->height / 2;
	p.z *= fdf->cam->z_scale;
	p.x *= fdf->cam->zoom;
	p.y *= fdf->cam->zoom;
	p.z *= fdf->cam->zoom;
	if (fdf->cam->alpha != 0)
	{
		prev_y = (double)p.y;
		prev_z = (double)p.z;
		a = fdf->cam->alpha;
		p.z = (int)(-prev_y * sin(a) + prev_z * cos(a));
	}
	if (fdf->cam->projection == 1)
		iso_project(&p.x, &p.y, p.z);
	p.x += fdf->cam->x_offset;
	p.y += fdf->cam->y_offset;
	return (p);
}

t_point	project(t_point p, t_fdf *fdf)
{
	return (transform_point(p, fdf));
}
