/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:49:30 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 10:24:34 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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

static void	parse_line(char *line, t_point *points, int y, t_fdf *fdf)
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
		if (points[x].z < fdf->map->z_min)
			fdf->map->z_min = points[x].z;
		if (points[x].z > fdf->map->z_max)
			fdf->map->z_max = points[x].z;
		x++;
	}
	free_split(split);
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
	if (fd < 0)
		ft_error("Error: Cannot open file");
	line = get_next_line(fd);
	if (!line)
		ft_error("Error: Cannot read file");
	fdf->map->width = get_map_width(line);
	free(line);
	close(fd);
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
