/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 08:55:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/02 13:19:23 by dyeboa        ########   odam.nl         */
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
	t_gen	gen;
	t_map	*c_map;

	c_map = NULL;
	if (argc == 2)
	{
		c_map = init_map();
		parser(argv[1], c_map);
		validate_map(c_map);
	// print_map(c_map, c_map->map);
		mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
		if (!mlx)
			return (EXIT_FAILURE);
		init_gen(&gen, mlx, c_map);
	// printf("ymax = %d, xmax = %d\n\n", c_map->y_max, c_map->x_max);
	// print_map(c_map, gen.map);
		// clear_screen(&gen, 0x000000);
		drawMap2D(&gen);
		mlx_loop_hook(mlx, render_screen, &gen);
		mlx_key_hook(mlx, movement, &gen);
		mlx_loop(mlx);
		mlx_terminate(mlx);
	}
	free_t_map(c_map);
	return (EXIT_SUCCESS);
}

void bresenham(t_gen *gen, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	sx;
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





