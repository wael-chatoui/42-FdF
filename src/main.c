/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:46:12 by wael              #+#    #+#             */
/*   Updated: 2025/12/12 20:46:57 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fdf->mlx);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;
	mlx_image_t	*img;

	if (argc != 2)
		return (1);
	ft_bzero(&fdf, sizeof(fdf));
	parse_map(argv[1], &fdf);
	init_mlx(&fdf);
	if (!fdf.mlx)
		ft_error();
	img = mlx_new_image(fdf.mlx, 256, 256);
	if (!img || mlx_image_to_window(fdf.mlx, img, 0, 0) < 0)
		ft_error();
	draw_map(img);
	mlx_key_hook(fdf.mlx, key_handler, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, fdf.mlx);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (0);
}
