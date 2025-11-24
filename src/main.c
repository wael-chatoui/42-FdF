/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:46:12 by wael              #+#    #+#             */
/*   Updated: 2025/11/22 21:52:48 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(int keycode, t_fdf *fdf)
{
	(void)fdf;
	if (keycode == 65307)  // ESC key
	{
		exit(0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (1);

	ft_printf("parsing...\n");
	parse_map(argv[1], &fdf);
	ft_printf("parsed: \nwidth = %d\n height = %d\n");
	init_mlx(&fdf);
//	draw_map(&fdf);

    mlx_key_hook(fdf.win, key_handler, &fdf);
    mlx_loop(fdf.mlx);
	return (0);
}
