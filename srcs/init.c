/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:55:31 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/03 18:53:33 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	map->txtrs.NO = NULL;
	map->txtrs.SO = NULL;
	map->txtrs.WE = NULL;
	map->txtrs.EA = NULL;
	map->txtrs.C = 0;
	map->txtrs.F = 0;
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
	// for (int i = 0; gen->map[i]; i++)
	// 	printf("%s\n", gen->map[i]);
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->bg = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->minimap = mlx_new_image(mlx, SIZE, SIZE);
	gen->width = cmap->x_max;
	gen->height = cmap->y_max;
	gen->draw = 1;
	if (gen->width < gen->height)
		gen->sq_size = SIZE / gen->width;
	else
		gen->sq_size = SIZE / gen->height;
	if (gen->sq_size < 4)
		gen->sq_size = 4;
	if (gen->sq_size > 32)
		gen->sq_size = 32;
	printf("sq_size = %d\n", gen->sq_size);
	init_player(gen, mlx, cmap);
}