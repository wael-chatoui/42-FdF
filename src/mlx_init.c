/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:02:26 by wael              #+#    #+#             */
/*   Updated: 2025/12/12 20:48:25 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX42\n", 2);
		exit(EXIT_FAILURE);
	}
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		mlx_terminate(fdf->mlx);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
	{
		ft_putstr_fd("Error: Failed to display image\n", 2);
		mlx_terminate(fdf->mlx);
		exit(EXIT_FAILURE);
	}
}
