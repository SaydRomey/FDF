/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:27:22 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/05 14:48:44 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/*
function to initialize the t_param struct of fdf to default values
*/
void	set_default(t_param *param, t_map map)
{
	double	width_scale;
	double	height_scale;
	int		grid_width_scaled;
	int		grid_height_scaled;

	width_scale = (WIDTH * RATIO) / map.cols;
	height_scale = (HEIGHT * RATIO) / map.rows;
	if (width_scale < height_scale)
		param->scale = width_scale;
	else
		param->scale = height_scale;
	grid_width_scaled = map.cols * param->scale;
	grid_height_scaled = map.rows * param->scale;
	param->x_offset = (WIDTH - grid_width_scaled) / 2;
	param->y_offset = (HEIGHT - grid_height_scaled) / 2;
	param->z_scale = 2;
	param->z_angle = 0;
	param->toggle.menu = OFF;
	param->toggle.color = OFF;
	param->toggle.iso = ON;
	param->toggle.row = ON;
	param->toggle.col = ON;
}

int	fdf_text(t_fdf *fdf, char *str, int x, int y)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y, TEXT_COLOR, str);
	return (0);
}

void	display_menu(t_fdf *fdf)
{
	int	x;
	int	y;
	int	incr;

	x = MENU_X;
	y = MENU_Y;
	incr = MENU_INCR;
	fdf_text(fdf, "(H)ide menu", x, y);
	fdf_text(fdf, "Move with 'WASD' or ARROWS", x, (y + incr));
	fdf_text(fdf, "Scale with '- / +'", x, (y + incr * 2));
	fdf_text(fdf, "Change Z scale with 'Q / E'", x, (y + incr * 3));
	fdf_text(fdf, "Rotate with 'Z / X'", x, (y + incr * 4));
	fdf_text(fdf, "Toggle colors with 'SPACE'", x, (y + incr * 5));
	fdf_text(fdf, "Toggle isometric/top view with 'I'", x, (y + incr * 6));
	fdf_text(fdf, "Toggle row lines with '1'", x, (y + incr * 7));
	fdf_text(fdf, "Toggle column lines with '2'", x, (y + incr * 8));
	fdf_text(fdf, "Reset to default with 'BACKSPACE'", x, (y + incr * 9));
	fdf_text(fdf, "Quit with 'ESC'", x, (y + incr * 10));
}

void	toggle(int *toggle)
{
	if (*toggle == ON)
		*toggle = OFF;
	else
		*toggle = ON;
}

void	proof(char *msg)
{
	ft_printf("%s\n", msg);
}
