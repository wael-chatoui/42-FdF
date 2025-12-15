/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:49:30 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 21:31:03 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map_width(char *line)
{
	int		width;
	char	**split;

	width = 0;
	split = ft_split(line, ' ');
	if (!split)
		ft_error("Error: Memory allocation failed");
	while (split[width] && split[width][0] != '\n')
		width++;
	free_split(split);
	return (width);
}

int	get_map_height(char *file)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error: Cannot open file");
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	get_color(char *str)
{
	char	*comma;
	int		color;

	comma = ft_strchr(str, ',');
	if (comma)
	{
		comma++;
		if (comma[0] == '0' && (comma[1] == 'x' || comma[1] == 'X'))
			color = ft_atoi_base(comma + 2, "0123456789ABCDEF");
		else
			color = ft_atoi(comma);
		return (color);
	}
	return (-1);
}

void	fill_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Error: Cannot open file");
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		fdf->map->points[y] = malloc(sizeof(t_point) * fdf->map->width);
		if (!fdf->map->points[y])
			ft_error("Error: Memory allocation failed");
		parse_line(line, fdf->map->points[y], y, fdf);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}

void	parse_map(char *file, t_fdf *fdf)
{
	char	*line;
	int		fd;

	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		ft_error("Error: Memory allocation failed");
	fdf->map->height = get_map_height(file);
	if (fdf->map->height == 0)
		ft_error("Error: Empty map");
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error("Error: Cannot open/read file");
	fdf->map->width = get_map_width(line);
	(free(line), close(fd));
	if (fdf->map->width == 0)
		ft_error("Error: Invalid map width");
	fdf->map->z_min = 0;
	fdf->map->z_max = 0;
	fdf->map->has_colors = 0;
	fdf->map->points = malloc(sizeof(t_point *) * fdf->map->height);
	if (!fdf->map->points)
		ft_error("Error: Memory allocation failed");
	fill_map(file, fdf);
}
