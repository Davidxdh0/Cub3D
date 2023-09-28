/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:59:40 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/28 22:47:31 by dyeboa        ########   odam.nl         */
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
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			if (gen->map[y][x] > 0 && gen->map[y][x] != 'S')
				color = 255;
			else
				color = 0;
			draw_square(gen->mlx, x, y, color);
		} 
	}
}