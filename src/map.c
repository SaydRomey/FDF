/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:51:00 by sayd              #+#    #+#             */
/*   Updated: 2023/09/04 22:29:41 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	allocate_grid_memory(t_point ***points, int rows, int cols)
{
	int	row;

	*points = (t_point **)malloc(sizeof(t_point *) * rows);
	row = 0;
	while (row < rows)
	{
		(*points)[row] = (t_point *)malloc(sizeof(t_point) * cols);
		row++;
	}
}

/*
converts a string to a t_point
if the string contains a comma, the color is extracted from the string
else the color is set to 0
*/
static t_point	value_to_point(char *value)
{
	t_point	point;
	char	**split;

	point.x = 0;
	point.y = 0;
	point.z = ft_atoi(value);
	point.color = 0;
	split = ft_split(value, ',');
	if (split[1])
	{
		if (ft_strncmp(split[1], "0x", 2) == SAME)
			point.color = ft_atoi_base(split[1] + 2, 16);
		else
			point.color = ft_atoi_base(split[1], 16);
	}
	free_split(split);
	return (point);
}

static void	map_to_grid(t_map *map)
{
	int		row;
	int		col;
	t_list	*node;
	char	**tokens;

	allocate_grid_memory(&map->points, map->rows, map->cols);
	row = 0;
	node = map->data;
	while (node)
	{
		tokens = ft_split(node->content, ' ');
		col = 0;
		while (tokens[col])
		{
			map->points[row][col] = value_to_point(tokens[col]);
			col++;
		}
		free_split(tokens);
		node = node->next;
		row++;
	}
}

static int	get_map_width(char *line)
{
	int	i;
	int	width;
	int	in_value;

	i = 0;
	width = 0;
	in_value = FALSE;
	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]) == FALSE && in_value == FALSE)
		{
			toggle(&in_value);
			width++;
		}
		else if (ft_isspace(line[i]) == TRUE && in_value == TRUE)
			toggle(&in_value);
		i++;
	}
	return (width);
}

/*
store map lines in nodes of a linked list
*/
void	get_map_info(t_map *map, char *map_file)
{
	int		fd;
	char	*line;

	fd = open(map_file, READ);
	map->data = NULL;
	line = get_next_line(fd);
	map->cols = get_map_width(line);
	while (line)
	{
		ft_lstadd_back(&map->data, ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	map->rows = ft_lstsize(map->data);
	map_to_grid(map);
}
