/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 08:55:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/06 18:59:17 by bfranco       ########   odam.nl         */
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
		mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
		if (!mlx)
			return (EXIT_FAILURE);
		init_gen(&gen, mlx, c_map);
		draw_background(&gen);
		draw_minimap(&gen);
		mlx_loop_hook(mlx, movement, &gen);
		// mlx_scroll_hook(mlx, scrolling, &gen);
		mlx_loop(mlx);
		free_textures(gen);
		mlx_terminate(mlx);
		free_t_map(c_map);
	}
	return (EXIT_SUCCESS);
}

void bresenham(t_gen *gen, int x1, int y1, int x2, int y2)
{
	t_vector	d;
	t_vector	s;
	float		err;
	float		err2;

	d.x = abs(x2 - x1);
	d.y = -abs(y2 - y1);
	s.x = 1;
	if (x1 > x2)
		s.x = -0.1;
	s.y = 1;
	if (y1 > y2)
		s.y = -0.1;
	err = d.x + d.y;
	while (1)
	{
		if ((x1 <= WIDTH && x1 >= 0) && (y1 >= 0 && y1 <= HEIGHT))
			mlx_put_pixel(gen->minimap, x1, y1, 0xFF0000FF);
		if (x1 == x2 && y1 == y2)
			break ;
		err2 = 2 * err;
		if (err2 >= d.y)
		{
			err += d.y;
			x1 += s.x;
		}
		if (err2 <= d.x)
		{
			err += d.x;
			y1 += s.y;
		}
	}
}

void	render_screen(void *param)
{
	t_gen	*gen;
	int		x;

	gen = (t_gen *)param;
	x = 0;
	mlx_delete_image(gen->mlx, gen->win);
	gen->win = mlx_new_image(gen->mlx, WIDTH, HEIGHT);
	draw_minimap(gen);
	memset(gen->win->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	while (x < WIDTH)
	{
		cast_ray(gen, &gen->player, x);
		++x;
	}
	mlx_image_to_window(gen->mlx, gen->win, 0, 0);
	mlx_set_instance_depth(&gen->win->instances[0], 1);
	mlx_image_to_window(gen->mlx, gen->minimap, 0, 0);
	mlx_set_instance_depth(&gen->minimap->instances[0], 2);
	mlx_image_to_window(gen->mlx, gen->player.img, gen->player.x * gen->sq_size, gen->player.y * gen->sq_size);
	mlx_set_instance_depth(&gen->player.img->instances[0], 3);
	gen->draw = 0;
}
