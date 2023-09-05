/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:59:46 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/05 14:57:27 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_UTILS_H
# define FDF_UTILS_H

/* grid to window (can be changed) */
# define RATIO			0.5

/* menu params */

# define TEXT_COLOR	WHITE
# define MENU_X			50
# define MENU_Y			50
# define MENU_INCR		20

/* grid colors (can be changed) */

# define COLOR_GRID		WHITE
# define COLOR_YESYES	GREEN
# define COLOR_NOYES	PURPLE
# define COLOR_YESNO	ORANGE

/* limits for modifications (can be changed) */

# define SCALE_MAX		500
# define SCALE_MIN		1
# define Z_MAX			42
# define Z_MIN			-42

/* x_event */
# define DESTROY		17

/* bytes per pixel */
# define PIXEL_SIZE		4

# define ISO_ANGLE		0.523599

/* colors */

# define BLACK			0x000000
# define WHITE			0xFFFFFF
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define YELLOW			0xFFFF00
# define MAGENTA		0xFF00FF
# define CYAN			0x00FFFF
# define ORANGE			0xED840C
# define ORANGE2		0xFF7700
# define PURPLE			0x800080
# define OLILAS			0xA27CF1
# define LILAC			0xFF22FF
# define PINK			0xFFC0CB
# define BROWN			0xA52A2A

#endif
