/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:20:08 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/02 21:39:19 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	scale(int key, t_fdf *fdf)
{
	int	scale_factor;
	int	z_scale_factor;

	scale_factor = 2;
	z_scale_factor = 2;
	if (key == PLUS && fdf->param.scale <= SCALE_MAX)
		fdf->param.scale += scale_factor;
	else if (key == MINUS && fdf->param.scale >= SCALE_MIN)
		fdf->param.scale -= scale_factor;
	else if (key == E && fdf->param.z_scale <= Z_MAX)
		fdf->param.z_scale += z_scale_factor;
	else if (key == Q && fdf->param.z_scale >= Z_MIN)
		fdf->param.z_scale -= z_scale_factor;
}

static void	rotate(int key, t_fdf *fdf)
{
	if (key == Z)
		fdf->param.z_angle += 0.1;
	else if (key == X)
		fdf->param.z_angle -= 0.1;
}

static void	translate(int key, t_fdf *fdf)
{
	if (key == W || key == UP)
		fdf->param.y_offset -= 10;
	else if (key == A || key == LEFT)
		fdf->param.x_offset -= 10;
	else if (key == S || key == DOWN)
		fdf->param.y_offset += 10;
	else if (key == D || key == RIGHT)
		fdf->param.x_offset += 10;
}

static void	flip_toggles(int key, t_fdf *fdf)
{
	if (key == H)
		toggle(&fdf->param.toggle.menu);
	else if (key == I)
		toggle(&fdf->param.toggle.iso);
	else if (key == K_1)
		toggle(&fdf->param.toggle.col);
	else if (key == K_2)
		toggle(&fdf->param.toggle.row);
	else if (key == SPACE)
		toggle(&fdf->param.toggle.color);
}

int	key_input(int key, t_fdf *fdf)
{
	ft_printf("key: %d\n", key);
	if (key == W || key == UP
		|| key == A || key == LEFT
		|| key == S || key == DOWN
		|| key == D || key == RIGHT)
		translate(key, fdf);
	else if (key == PLUS || key == MINUS || key == E || key == Q)
		scale(key, fdf);
	else if (key == Z || key == X)
		rotate(key, fdf);
	else if (key == H || key == I || key == K_1 || key == K_2 || key == SPACE)
		flip_toggles(key, fdf);
	else if (key == BACKSPACE)
		set_default(&fdf->param, fdf->map);
	else if (key == ESC)
		terminate_mlx(fdf);
	render(fdf);
	return (0);
}
