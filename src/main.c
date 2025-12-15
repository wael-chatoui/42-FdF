/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:46:12 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 22:31:43 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../minilibx-linux/mlx.h"

static void	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map.fdf>", 2);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".fdf", 4) != 0)
	{
		ft_putendl_fd("Error: Invalid file format (must be .fdf)", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	check_args(argc, argv);
	ft_bzero(&fdf, sizeof(t_fdf));
	parse_map(argv[1], &fdf);
	init_fdf(&fdf);
	draw(&fdf);
	mlx_hook(fdf.win, 17, 0, (int (*)())(void *)close_window, &fdf);
	mlx_key_hook(fdf.win, handle_key, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
