/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:15:26 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/04 22:05:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	cleanup_map(t_map *map)
{
	int	row;

	proof("Cleaning up map->points");
	if (map->points)
	{
		row = 0;
		while (row < map->rows)
		{
			safe_free((void **)&map->points[row]);
			row++;
		}
		safe_free((void **)&map->points);
	}
	proof("Cleaning up map->data");
	if (map->data)
	{
		ft_lstclear(&map->data, free);
		map->data = NULL;
	}
}

int	terminate_mlx(t_fdf *fdf)
{
	cleanup_map(&fdf->map);
	proof("Terminating mlx");
	safe_free((void **)&fdf->mlx_ptr);
	exit(SUCCESS);
}
