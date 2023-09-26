/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:59:40 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/26 14:28:46 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(mlx_t *mlx, int x, int y, int color)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, SIZE / 2, SIZE / 2);
	memset(img->pixels, color, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, x * SIZE / 2, y * SIZE / 2);
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
			if (gen->map[y][x] > 0)
				color = 255;
			else
				color = 0;
			draw_square(gen->mlx, x, y, color);
		} 
	}
}