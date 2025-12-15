/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:28:07 by wael              #+#    #+#             */
/*   Updated: 2025/12/15 10:25:03 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	free_map(t_fdf *fdf)
{
	int	i;

	if (!fdf->map)
		return ;
	if (fdf->map->points)
	{
		i = 0;
		while (i < fdf->map->height)
		{
			if (fdf->map->points[i])
				free(fdf->map->points[i]);
			i++;
		}
		free(fdf->map->points);
	}
	free(fdf->map);
	fdf->map = NULL;
}
