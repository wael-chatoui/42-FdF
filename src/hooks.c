/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:00:00 by wael              #+#    #+#             */
/*   Updated: 2025/12/14 17:55:44 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx-linux/mlx.h"

static void	handle_zoom(int key, t_fdf *fdf)
{
	if (key == KEY_PLUS)
	{
		if (fdf->cam->zoom < 100)
			fdf->cam->zoom += 2;
	}
	else if (key == KEY_MINUS)
	{
		if (fdf->cam->zoom > 1)
			fdf->cam->zoom -= 2;
	}
}

static void	handle_move(int key, t_fdf *fdf)
{
	if (key == KEY_LEFT)
		fdf->cam->x_offset -= 10;
	else if (key == KEY_RIGHT)
		fdf->cam->x_offset += 10;
	else if (key == KEY_UP)
		fdf->cam->y_offset -= 10;
	else if (key == KEY_DOWN)
		fdf->cam->y_offset += 10;
}

static void	handle_rotate(int key, t_fdf *fdf)
{
	if (key == KEY_W)
		fdf->cam->alpha += 0.05;
	else if (key == KEY_S)
		fdf->cam->alpha -= 0.05;
	else if (key == KEY_A)
		fdf->cam->beta -= 0.05;
	else if (key == KEY_D)
		fdf->cam->beta += 0.05;
	else if (key == KEY_Q)
		fdf->cam->gamma -= 0.05;
	else if (key == KEY_E)
		fdf->cam->gamma += 0.05;
}

int	key_press(int key, t_fdf *fdf)
{
	if (key == KEY_ESC)
		close_window(fdf);
	else if (key == KEY_PLUS || key == KEY_MINUS)
		handle_zoom(key, fdf);
	else if (key == KEY_LEFT || key == KEY_RIGHT ||
			key == KEY_UP || key == KEY_DOWN)
		handle_move(key, fdf);
	else if (key == KEY_W || key == KEY_S || key == KEY_A ||
			key == KEY_D || key == KEY_Q || key == KEY_E)
		handle_rotate(key, fdf);
	else if (key == KEY_P)
		fdf->cam->projection = !fdf->cam->projection;
	else if (key == KEY_R)
		reset_cam(fdf);
	draw(fdf);
	return (0);
}

int	mouse_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == MOUSE_LEFT)
	{
		fdf->mouse->is_pressed = 1;
		fdf->mouse->prev_x = x;
		fdf->mouse->prev_y = y;
	}
	else if (button == MOUSE_SCROLL_UP)
	{
		if (fdf->cam->z_scale < 10)
			fdf->cam->z_scale += 0.1;
		draw(fdf);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		if (fdf->cam->z_scale > 0.1)
			fdf->cam->z_scale -= 0.1;
		draw(fdf);
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		fdf->mouse->is_pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse->is_pressed)
	{
		fdf->cam->beta += (x - fdf->mouse->prev_x) * 0.002;
		fdf->cam->alpha += (y - fdf->mouse->prev_y) * 0.002;
		fdf->mouse->prev_x = x;
		fdf->mouse->prev_y = y;
		draw(fdf);
	}
	return (0);
}

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
