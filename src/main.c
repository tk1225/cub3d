/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terabu <terabu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:32:12 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/07/03 11:52:10 by terabu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	window_reflesh(t_vars *vars, int width, int height)
{
	t_data	black_img;

	black_img.img = mlx_new_image(vars->mlx, width, height);
	black_img.addr = mlx_get_data_addr(black_img.img, \
	&black_img.bits_per_pixel, &black_img.line_length, &black_img.endian);
	mlx_put_image_to_window(vars->mlx, \
	vars->win, black_img.img, 0, 0);
}

int	render_next_frame(t_vars *vars)
{
	window_reflesh(vars, SCREEN_WIDTH, SCREEN_HEIGHT);
	raycasting(vars);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	check_pre(argc, argv);
	vars = (t_vars *)malloc(sizeof(t_vars));
	initialized(vars, argv[1]);
	raycasting(vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_hook(vars->win, 2, 1L << 0, key_handle, vars);
	mlx_loop(vars->mlx);
}

__attribute((destructor))
static void destructor() {
    system("leaks -q cub3d");
}

// static int	file_open(char *filename)
// {
// 	int	fd;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_putstr_fd("Error\n", 1);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (fd);
// }

// static t_mapdata	map_info_init(int argc, char *argv[])
// {
// 	int			fd;
// 	t_mapdata	map_info;

// 	if (argc >= 3 || argc == 1)
// 		exit(EXIT_FAILURE);
// 	fd = file_open(argv[1]);
// 	map_info = measure_mapdata(fd);
// 	close(fd);
// 	return (map_info);
// }

// int	main(int argc, char *argv[])
// {
// 	int			fd;
// 	t_mapdata	map_info;
// 	char		**map_index;

// 	map_info = map_info_init(argc, argv);
// 	if (map_info.error_flag == ERROR)
// 	{
// 		ft_putstr_fd("Error\n", 1);
// 		exit(EXIT_FAILURE);
// 	}
// 	fd = file_open(argv[1]);
// 	map_index = map_index_init(fd, map_info);
// 	close(fd);
// 	if (map_info.error_flag == ERROR || \
// 	error_handle(map_index, map_info) == ERROR)
// 	{
// 		ft_putstr_fd("Error\n", 1);
// 		exit(EXIT_FAILURE);
// 	}
// 	game_start(map_index, map_info);
// 	free_map(map_info, map_index);
// 	return (0);
// }

// __attribute__((destructor)) static void destructor(){
// 	system("leaks -q so_long");
// }
