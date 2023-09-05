/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:42:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/04 22:54:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	clear_image(t_img *img)
{
	int	total_pixels;

	total_pixels = WIDTH * HEIGHT * PIXEL_SIZE;
	ft_bzero(img->addr, total_pixels);
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*image_data;
	int		pixel_index;
	int		byte_offset;
	int		*pixel_location;

	image_data = img->addr;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_index = (x + y * WIDTH);
		byte_offset = pixel_index * PIXEL_SIZE;
		pixel_location = (int *)(image_data + byte_offset);
		*pixel_location = color;
	}
}

/*
(color from file always win)
change colors with macros in colors.h
*/
int	palette(int color_toggle, int start_z, int end_z, int color)
{
	if (color_toggle == OFF && color == 0)
		return (WHITE);
	else if (color_toggle == ON && color == 0)
	{
		if (start_z != 0 && end_z != 0)
			color = COLOR_YESYES;
		else if (start_z == 0 && end_z != 0)
			color = COLOR_NOYES;
		else if (start_z != 0 && end_z == 0)
			color = COLOR_YESNO;
		else
			color = COLOR_GRID;
	}
	return (color);
}
