/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:02:26 by wael              #+#    #+#             */
/*   Updated: 2025/12/14 17:53:25 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx-linux/mlx.h"

void	init_cam(t_fdf *fdf)
{
	fdf->cam = malloc(sizeof(t_cam));
	if (!fdf->cam)
		ft_error("Error: Memory allocation failed");
	fdf->cam->zoom = ft_min(WIDTH / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
	if (fdf->cam->zoom < 1)
		fdf->cam->zoom = 1;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->z_scale = 1.0;
	fdf->cam->x_offset = WIDTH / 2;
	fdf->cam->y_offset = HEIGHT / 2;
	fdf->cam->projection = 1;
}

void	init_mouse(t_fdf *fdf)
{
	fdf->mouse = malloc(sizeof(t_mouse));
	if (!fdf->mouse)
		ft_error("Error: Memory allocation failed");
	fdf->mouse->is_pressed = 0;
	fdf->mouse->x = 0;
	fdf->mouse->y = 0;
	fdf->mouse->prev_x = 0;
	fdf->mouse->prev_y = 0;
}

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		ft_error("Error: Failed to initialize MLX");
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF - 42");
	if (!fdf->win)
		ft_error("Error: Failed to create window");
	fdf->img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img.img)
		ft_error("Error: Failed to create image");
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.line_len, &fdf->img.endian);
	if (!fdf->img.addr)
		ft_error("Error: Failed to get image data");
	init_cam(fdf);
	init_mouse(fdf);
}

void	reset_cam(t_fdf *fdf)
{
	fdf->cam->zoom = ft_min(WIDTH / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
	if (fdf->cam->zoom < 1)
		fdf->cam->zoom = 1;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->z_scale = 1.0;
	fdf->cam->x_offset = WIDTH / 2;
	fdf->cam->y_offset = HEIGHT / 2;
}
