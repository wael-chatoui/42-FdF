/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:49:30 by wael              #+#    #+#             */
/*   Updated: 2025/12/12 20:43:17 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_width(char *buf)
{
	int	count;

	count = 0;
	while (*buf && *buf != '\n')
	{
		if (*buf && (ft_isdigit(*buf) || *buf == '-'))
			buf++;
		if (*buf && ft_isspace(*buf))
			count++;
		buf++;
	}
	return (count);
}

void	parse_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	fdf->height = 0;
	line = get_next_line(fd);
	if (line)
		fdf->width = get_width(line);
	while (line)
	{
		fdf->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
