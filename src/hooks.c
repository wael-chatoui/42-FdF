/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:00:00 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 21:30:03 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx-linux/mlx.h"

int	close_window(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free_map(fdf);
	if (fdf->cam)
		free(fdf->cam);
	if (fdf->mouse)
		free(fdf->mouse);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	if (keycode == KEY_P)
	{
		if (fdf->cam->projection == 1)
			fdf->cam->projection = 0;
		else
			fdf->cam->projection = 1;
		draw(fdf);
	}
	return (0);
}
