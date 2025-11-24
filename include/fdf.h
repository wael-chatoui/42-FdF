/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:27:23 by wael              #+#    #+#             */
/*   Updated: 2025/11/22 19:12:11 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1280
# define HEIGHT 720
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

	int		**map;
	int		width;
	int		height;

	// int		zoom;
	// int		z_scale;
	// int		x_offset;
	// int		y_offset;
}	t_fdf;

void	parse_map(char *file, t_fdf *fdf);
void	init_mlx(t_fdf *fdf);
int		key_handler(int keycode, t_fdf *fdf);

#endif
