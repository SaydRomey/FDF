/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:28:36 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/05 14:53:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/inc/libft.h"
# include "fdf_utils.h"
# include <math.h>

# ifdef __APPLE__
#  include "../minilibx_macos/mlx.h"
#  include "key_macos.h"
#  define WIDTH 2560
#  define HEIGHT 1395
# else
#  ifdef __linux__
#   include "../minilibx_linux/mlx.h"
#   include "key_linux.h"
#   define WIDTH 1366
#   define HEIGHT 768
#  endif
# endif

typedef struct s_toggle
{
	int			color;
	int			menu;
	int			iso;
	int			row;
	int			col;
}				t_toggle;

typedef struct t_param
{
	double		scale;
	int			z_scale;
	int			x_offset;
	int			y_offset;
	float		z_angle;
	t_toggle	toggle;
}				t_param;

typedef struct s_point
{
	float		x;
	float		y;
	int			z;
	int			color;
}				t_point;

typedef struct s_map
{
	t_list		*data;
	t_point		**points;
	int			rows;
	int			cols;
}				t_map;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_fdf
{
	char		*title;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		map;
	t_param		param;
}				t_fdf;

/* main.c */
int				main(int arc, char **argv);

/* map.c */
void			get_map_info(t_map *map, char *map_file);

/* transform.c */
t_point			transform(t_point point, t_param *param, int z);

/* draw.c */
void			render(t_fdf *fdf);

/* draw_utils.c */
void			clear_image(t_img *img);
void			draw_pixel(t_img *img, int x, int y, int color);
int				palette(int color_toggle, int start_z, int end_z, int color);

/* hooks.c */
int				key_input(int key, t_fdf *fdf);

/* cleanup.c */
int				terminate_mlx(t_fdf *fdf);

/* utils.c*/
void			set_default(t_param *param, t_map map);
int				fdf_text(t_fdf *fdf, char *str, int x, int y);
void			display_menu(t_fdf *fdf);
void			toggle(int *toggle);
void			proof(char *msg);

#endif
