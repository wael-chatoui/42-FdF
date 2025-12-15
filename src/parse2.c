/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:32:22 by wchatoui          #+#    #+#             */
/*   Updated: 2025/12/15 20:50:24 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	parse_line_step(t_point *points, t_fdf *fdf, int x)
{
	if (points[x].z < fdf->map->z_min)
		fdf->map->z_min = points[x].z;
	if (points[x].z > fdf->map->z_max)
		fdf->map->z_max = points[x].z;
}

void	parse_line(char *line, t_point *points, int y, t_fdf *fdf)
{
	char	**split;
	int		x;
	int		color;

	split = ft_split(line, ' ');
	if (!split)
		ft_error("Error: Memory allocation failed");
	x = 0;
	while (split[x] && split[x][0] != '\n')
	{
		points[x].x = x;
		points[x].y = y;
		points[x].z = ft_atoi(split[x]);
		color = get_color(split[x]);
		if (color != -1)
		{
			points[x].color = color;
			fdf->map->has_colors = 1;
		}
		else
			points[x].color = -1;
		parse_line_step(points, fdf, x);
		x++;
	}
	free_split(split);
}
