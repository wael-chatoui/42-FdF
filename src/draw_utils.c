/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:00:00 by wael              #+#    #+#             */
/*   Updated: 2025/12/14 17:55:16 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx-linux/mlx.h"

static void	draw_menu_background(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < MENU_WIDTH)
		{
			put_pixel(fdf, x, y, COLOR_MENU_BG);
			x++;
		}
		y++;
	}
}

static void	put_string(t_fdf *fdf, int x, int y, char *str)
{
	mlx_string_put(fdf->mlx, fdf->win, x, y, COLOR_TEXT, str);
}

void	draw_menu(t_fdf *fdf)
{
	int		y;
	char	*str;

	y = 20;
	draw_menu_background(fdf);
	put_string(fdf, 10, y, "=== FdF Controls ===");
	y += 30;
	put_string(fdf, 10, y, "Zoom: + / -");
	y += 20;
	put_string(fdf, 10, y, "Move: Arrow Keys");
	y += 20;
	put_string(fdf, 10, y, "Rotate X: W / S");
	y += 20;
	put_string(fdf, 10, y, "Rotate Y: A / D");
	y += 20;
	put_string(fdf, 10, y, "Rotate Z: Q / E");
	y += 20;
	put_string(fdf, 10, y, "Z Scale: Mouse Scroll");
	y += 20;
	put_string(fdf, 10, y, "Projection: P (Iso/Para)");
	y += 20;
	put_string(fdf, 10, y, "Reset: R");
	y += 20;
	put_string(fdf, 10, y, "Exit: ESC");
	y += 40;
	put_string(fdf, 10, y, "=== Map Info ===");
	y += 30;
	str = ft_itoa(fdf->map->width);
	put_string(fdf, 10, y, "Width: ");
	put_string(fdf, 80, y, str);
	free(str);
	y += 20;
	str = ft_itoa(fdf->map->height);
	put_string(fdf, 10, y, "Height: ");
	put_string(fdf, 80, y, str);
	free(str);
	y += 20;
	str = ft_itoa(fdf->map->z_min);
	put_string(fdf, 10, y, "Z Min: ");
	put_string(fdf, 80, y, str);
	free(str);
	y += 20;
	str = ft_itoa(fdf->map->z_max);
	put_string(fdf, 10, y, "Z Max: ");
	put_string(fdf, 80, y, str);
	free(str);
}
