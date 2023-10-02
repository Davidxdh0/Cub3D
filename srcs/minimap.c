/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:59:40 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/02 21:27:17 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(mlx_t *mlx, int x, int y, int color)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, SIZE / 4, SIZE / 4);
	memset(img->pixels, color, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, x * SIZE / 4, y * SIZE / 4);
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
				color = 0x0;
			draw_square(gen->mlx, x, y, color);
			//printf("map[%d][%d] = %c\n", y, x, gen->map[y][x]);
		} 
	}
	// else
	// 	scaled_minimap(t_gen *gen);
}

// void scaled_minimap(t_gen *gen)
// {
	
// }