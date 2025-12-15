/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:02:26 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 22:40:11 by wchatoui         ###   ########.fr       */
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
	fdf->cam->alpha = 0.523599;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->z_scale = .5;
	fdf->cam->x_offset = WIDTH / 2;
	fdf->cam->y_offset = HEIGHT / 2;
	fdf->cam->projection = 1;
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
}
