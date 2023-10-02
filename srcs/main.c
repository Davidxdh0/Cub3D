/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 08:55:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/02 09:00:18 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "cub3d.h"

//valgrind --leak-check=full --show-leak-kinds=all 
// --track-origins=yes ./cub3D maps/default.cub
int	main(int argc, char *argv[])
{
	mlx_t	*mlx;
	// t_gen	gen;
	t_map	*c_map;

	c_map = NULL;
	if (argc == 2)
	{
		c_map = init_map();
		parser(argv[1], c_map);
		// print_map(c_map, c_map->map);
		validate_map(c_map);
		print_map(c_map, c_map->map);
		mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
		if (!mlx)
			return (EXIT_FAILURE);
		// init_gen(&gen, mlx, c_map->map);
		// print_map(c_map, gen.map);
		// clear_screen(&gen, 0x000000);
		// drawMap2D(&gen);
		// mlx_loop_hook(mlx, render_screen, &gen);
		// mlx_key_hook(mlx, movement, &gen);
		// mlx_loop(mlx);
		mlx_terminate(mlx);
	}
	free_t_map(c_map);
	return (EXIT_SUCCESS);
}

// int map[MAP_WIDTH][MAP_HEIGHT] = 
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,1,3,3,3,3,3,3,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,1,1,1,3,3,3,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

void bresenham(t_gen *gen, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	sx;
 	// create mode 100644 srcs/map_parser/file_handling.c
	int	sy;
	int	err;
	int	err2;

	dx = abs(x2 - x1);
	dy = -abs(y2 - y1);
	sx = 1;
	if (x1 > x2)
		sx = -1;
	sy = 1;
	if (y1 > y2)
		sy = -1;
	err = dx + dy;
	while (x1 != x2 && y1 != y2)
	{
		mlx_put_pixel(gen->win, x1, y1, 0xFF0000FF);
		err2 = 2 * err;
		if (err2 >= dy && x1 != x2)
		{
			err += dy;
			x1 += sx;
		}
		if (err2 <= dx && y1 != y2)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	render_screen(void *param)
{
	t_gen	*gen;
	int		x;

	gen = (t_gen *)param;
	x = 0;
	memset(gen->win->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	while (x < WIDTH)
	{
		cast_ray(gen, &gen->player, x);
		++x;
	}
	mlx_image_to_window(gen->mlx, gen->win, 0, 0);
}

// char **create_map(void)
// {
// 	char	**my_map;
// 	int	i;
// 	int	j;

// 	my_map = malloc(sizeof(char *) * MAP_HEIGHT);
// 	if (!my_map)
// 		return (NULL);
// 	i = 0;
// 	while (i < MAP_HEIGHT)
// 	{
// 		my_map[i] = malloc(sizeof(char) * MAP_WIDTH);
// 		if (!my_map[i])
// 			return (NULL);
// 		j = 0;
// 		while (j < MAP_WIDTH)
// 		{
// 			my_map[i]ATTENTION: default value of option mesa_glthread overridden by environment.[j] = map[i][j];
// 			++j;
// 		}
// 		++i;
// 	}
// 	return (my_map);
// }

void	init_gen(t_gen *gen, mlx_t *mlx, char** map)
{
	gen->mlx = mlx;
	gen->map = map;
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->player.x = 12;
	gen->player.y = 22;
	gen->player.dir_x = -1;
	gen->player.dir_y = 0;
	gen->player.plane_x = 0;
	gen->player.plane_y = 0.90;
	gen->player.img = mlx_new_image(mlx, SIZE / 8, SIZE / 8);
	for (int i = 0; i < SIZE / 8; i++)
		for (int j = 0; j < SIZE / 8; j++)
				mlx_put_pixel(gen->player.img, i, j, 0xFF00FFFF);
	mlx_image_to_window(gen->mlx, gen->player.img, gen->player.x * SIZE / 4, gen->player.y * SIZE / 4);
}



