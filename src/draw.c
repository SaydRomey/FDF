/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:04:13 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/05 15:00:38 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	draw_line(t_fdf *fdf, t_point start, t_point end)
{
	t_point	step;
	int		max;
	int		start_z;
	int		end_z;
	int		color;

	start_z = fdf->map.points[(int)start.y][(int)start.x].z;
	end_z = fdf->map.points[(int)end.y][(int)end.x].z;
	color = palette(fdf->param.toggle.color, start_z, end_z,
			fdf->map.points[(int)start.y][(int)start.x].color);
	start = transform(start, &(fdf->param), start_z);
	end = transform(end, &(fdf->param), end_z);
	step.x = end.x - start.x;
	step.y = end.y - start.y;
	max = ft_max(ft_abs(step.x), ft_abs(step.y));
	step.x /= max;
	step.y /= max;
	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		draw_pixel(&(fdf->img), start.x, start.y, color);
		start.x += step.x;
		start.y += step.y;
	}
}

static void	draw_row(t_fdf *fdf, int row, int col)
{
	t_point	start;
	t_point	end;

	start.x = col;
	start.y = row;
	if (col < fdf->map.cols - 1)
	{
		end.x = col + 1;
		end.y = row;
		draw_line(fdf, start, end);
	}
}

static void	draw_col(t_fdf *fdf, int row, int col)
{
	t_point	start;
	t_point	end;

	start.x = col;
	start.y = row;
	if (row < fdf->map.rows - 1)
	{
		end.x = col;
		end.y = row + 1;
		draw_line(fdf, start, end);
	}
}

static void	draw_map(t_fdf *fdf)
{
	int	row;
	int	col;

	row = 0;
	while (row < fdf->map.rows)
	{
		col = 0;
		while (col < fdf->map.cols)
		{
			if (fdf->param.toggle.row == ON)
				draw_row(fdf, row, col);
			if (fdf->param.toggle.col == ON)
				draw_col(fdf, row, col);
			col++;
		}
		row++;
	}
}

void	render(t_fdf *fdf)
{
	proof("Rendering");
	clear_image(&(fdf->img));
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
	if (fdf->param.toggle.menu == ON)
		display_menu(fdf);
	else
		fdf_text(fdf, "(H)elp", MENU_X, MENU_Y);
}
