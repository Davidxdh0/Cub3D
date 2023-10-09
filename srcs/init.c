/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:55:31 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 13:25:26 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "player.h"
#include "cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	map->txtrs.no = NULL;
	map->txtrs.so = NULL;
	map->txtrs.we = NULL;
	map->txtrs.ea = NULL;
	map->txtrs.ceil = 0;
	map->txtrs.floor = 0;
	map->map = NULL;
	map->start_y = -1;
	map->start_x = -1;
	map->y_start = -1;
	map->x_start = -1;
	map->y_max = -1;
	map->x_max = -1;
	map->error = 0;
	return (map);
}

//check for errors
void	init_textures(t_gen *gen)
{
	gen->txtrs.t_no = mlx_load_png(gen->txtrs.no);
	gen->txtrs.t_so = mlx_load_png(gen->txtrs.so);
	gen->txtrs.t_we = mlx_load_png(gen->txtrs.we);
	gen->txtrs.t_ea = mlx_load_png(gen->txtrs.ea);
	if (!gen->txtrs.t_no || !gen->txtrs.t_so \
	|| !gen->txtrs.t_we || !gen->txtrs.t_ea)
	{
		free_textures(gen);
		error_exit("Failed to load textures");
	}
}

void	init_gen(t_gen *gen, mlx_t *mlx, t_map *cmap)
{
	gen->mlx = mlx;
	gen->map = cmap->map;
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->bg = mlx_new_image(mlx, WIDTH, HEIGHT);
	gen->minimap = mlx_new_image(mlx, SIZE, SIZE);
	gen->width = cmap->x_max;
	gen->height = cmap->y_max;
	gen->draw = 1;
	if (gen->width > gen->height)
		gen->sq_size = SIZE / gen->width;
	else
		gen->sq_size = SIZE / gen->height;
	if (gen->sq_size < 4)
		gen->sq_size = 4;
	if (gen->sq_size > 32)
		gen->sq_size = 32;
	init_player(gen, mlx, cmap);
	init_textures(gen);
}
