/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:52:04 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/04 22:38:13 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	validate_arguments(int argc, char **argv)
{
	int		check;
	char	*extension;

	if (argc != 2)
		va_exit_error("Usage: %s <filename>.fdf", argv[0]);
	extension = ft_strrchr(argv[1], '.');
	if (!extension || ft_strrncmp(extension, ".fdf", 4) != SAME)
		va_exit_error("Error: invalid file extension");
	check = read_check(argv[1]);
	if (check == 0)
		va_exit_error("Error: file is empty -> %s", argv[1]);
	else if (check == -1)
		va_exit_error("Error: could not open or read -> %s", argv[1]);
	proof("Valid arguments");
}

/*
initializes mlx, window, image elements of t_fdf
*/
static t_fdf	initiate_fdf(char *path)
{
	t_fdf	fdf;
	char	*title;

	title = ft_strjoin("FdF - ", path);
	proof("Initiating mlx");
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIDTH, HEIGHT, title);
	safe_free((void **)&title);
	fdf.img.img_ptr = mlx_new_image(fdf.mlx_ptr, WIDTH, HEIGHT);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img_ptr, &fdf.img.bpp,
			&fdf.img.line_length, &fdf.img.endian);
	return (fdf);
}

/* 
handles first rendering, sets the hooks, then loops the mlx
*/
static void	fdf_loop(t_fdf *fdf)
{
	render(fdf);
	mlx_key_hook(fdf->win_ptr, key_input, fdf);
	mlx_hook(fdf->win_ptr, DESTROY, 0, terminate_mlx, fdf);
	mlx_loop(fdf->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	validate_arguments(argc, argv);
	fdf = initiate_fdf(argv[1]);
	get_map_info(&fdf.map, argv[1]);
	set_default(&fdf.param, fdf.map);
	fdf_loop(&fdf);
	terminate_mlx(&fdf);
	return (SUCCESS);
}
