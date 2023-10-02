/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:55:31 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/02 14:37:25 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->txtrs.NO = NULL;
	map->txtrs.SO = NULL;
	map->txtrs.WE = NULL;
	map->txtrs.EA = NULL;
	map->txtrs.C = NULL;
	map->txtrs.F = NULL;
	map->map = NULL;
	map->startY = -1;
	map->startX = -1;
	map->y_start = -1;
	map->x_start = -1;
	map->y_max = -1;
	map->x_max = -1;
	return (map);
}

/*
camera direction: planeX & planeY - Make sure the camera plane is perpendicular to the direction
*/
void	init_gen(t_gen *gen, mlx_t *mlx, t_map *cmap)
{
	gen->mlx = mlx;
	gen->map = cmap->map;
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->width = cmap->x_max;
	gen->height = cmap->y_max;
	gen->draw = 1;
	gen->player.dir = cmap->dir;
	gen->player.x = cmap->x_start;
	gen->player.y = cmap->y_start;
	gen->player.dir_x = 0;
	gen->player.dir_y = -1;
	gen->player.plane_x = 0.66;
	gen->player.plane_y = 0;
	gen->player.img = mlx_new_image(mlx, SIZE / 8, SIZE / 8);
	for (int i = 0; i < SIZE / 8; i++)
		for (int j = 0; j < SIZE / 8; j++)
				mlx_put_pixel(gen->player.img, i, j, 0xFF00FFFF);
	mlx_image_to_window(gen->mlx, gen->player.img, gen->player.x * SIZE / 4, gen->player.y * SIZE / 4);
}