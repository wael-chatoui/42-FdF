/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:27:23 by wael              #+#    #+#             */
/*   Updated: 2025/12/12 18:34:33 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1280
# define HEIGHT 720
# include "libft.h"
# include <MLX42/MLX42.h>

typedef struct s_fdf
{
	mlx_t		*mlx;
	void		*win; /* kept for compatibility with existing code */
	mlx_image_t	*img;
	uint8_t		*addr; /* pixel buffer */
	int			bpp;
	int			line_len;
	int			endian;

	int			**map;
	int32_t		width;
	int32_t		height;

	// int		zoom;
	// int		z_scale;
	// int		x_offset;
	// int		y_offset;
}	t_fdf;

void	parse_map(char *file, t_fdf *fdf);
void	init_mlx(t_fdf *fdf);
void	key_handler(mlx_key_data_t keydata, void *param);
void	ft_error(void);
void	draw_map(mlx_image_t *img);

#endif
