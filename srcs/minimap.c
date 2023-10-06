/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:59:40 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/06 11:22:09 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_gen *gen, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * gen->sq_size;
	// printf("i = %d\n", i);
	while (i < (x + 1) * gen->sq_size && i < SIZE)
	{
		j = y * gen->sq_size;
		while (j < (y + 1) * gen->sq_size && j < SIZE)
		{
			mlx_put_pixel(gen->minimap, i, j, color);
			++j;
		}
		++i;
	}
}


void drawMap2D(t_gen *gen)
{
	int			x;
	int			y;
	int			color;

	y = -1;
	// x = gen->player.x
	// y = gen->player.y
	// if (gen->width < 10 && gen->heigh < 10)
	while (gen->map[++y])
	{
		x = -1;
		while (gen->map[y][++x])
		{
			if (gen->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x0000FF;
			// printf("draw square: ");
			draw_square(gen, x, y, color);
			//printf("map[%d][%d] = %c\n", y, x, gen->map[y][x]);
		} 
	}
	// else
	// 	scaled_minimap(t_gen *gen);
	mlx_image_to_window(gen->mlx, gen->minimap, 0, 0);
	mlx_set_instance_depth(&gen->minimap->instances[0], 1);
}

// void scaled_minimap(t_gen *gen)
// {
	
// }

void	draw_background(t_gen *gen)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = gen->txtrs.ceil;
		else
			color = gen->txtrs.floor;
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(gen->bg, x, y, color);
	}
	mlx_image_to_window(gen->mlx, gen->bg, 0, 0);
	mlx_set_instance_depth(&gen->bg->instances[0], 0);

}

/*
	minimap img size = (HEIGHT / 4) ^ 2
	
	1 square = (HEIGHT / 4) / gen->map->height
	or 
	1 square = (HEIGHT / 4) / gen->map->width
	deppending on which is smaller
	max sqaure = 32x32
	min square = 4x4

	player = (HEIGHT / 8)
	player max = 8x8
	player min = 4x4

	if 1 square <= player size
		hide player from minimap
		highlight square instead
*/