/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:00:00 by wael              #+#    #+#             */
/*   Updated: 2025/12/14 17:54:04 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, double alpha)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(int *x, int *z, double beta)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(beta) + *z * sin(beta);
	*z = -prev_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(int *x, int *y, double gamma)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(gamma) - prev_y * sin(gamma);
	*y = prev_x * sin(gamma) + prev_y * cos(gamma);
}

void	iso_project(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

t_point	transform_point(t_point p, t_fdf *fdf)
{
	p.x -= fdf->map->width / 2;
	p.y -= fdf->map->height / 2;
	p.z *= fdf->cam->z_scale;
	p.x *= fdf->cam->zoom;
	p.y *= fdf->cam->zoom;
	p.z *= fdf->cam->zoom;
	rotate_x(&p.y, &p.z, fdf->cam->alpha);
	rotate_y(&p.x, &p.z, fdf->cam->beta);
	rotate_z(&p.x, &p.y, fdf->cam->gamma);
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
