/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 14:51:52 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/03 18:24:33 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vert_plane(t_gen *gen)
{
	if (gen->player.dir == 'W')
	{
		gen->player.dir_x = -1;
		gen->player.dir_y = 0;
		gen->player.plane_x = 0;
		gen->player.plane_y = 0.66;
	}
	else if (gen->player.dir == 'E')
	{
		gen->player.dir_x = 1;
		gen->player.dir_y = 0;
		gen->player.plane_x = 0;
		gen->player.plane_y = -0.66;
	}
}

static void	init_horiz_plane(t_gen *gen)
{
	if (gen->player.dir == 'N')
	{
		gen->player.dir_x = 0;
		gen->player.dir_y = -1;
		gen->player.plane_x = -0.66;
		gen->player.plane_y = 0;
	}
	else if (gen->player.dir == 'S')
	{
		gen->player.dir_x = 0;
		gen->player.dir_y = 1;
		gen->player.plane_x = 0.66;
		gen->player.plane_y = 0;
	}
	else
		init_vert_plane(gen);
}

void	init_player(t_gen *gen, mlx_t *mlx, t_map *cmap)
{
	int	size;
	
	size = gen->sq_size / 2;
	if (size < 4)
		size = 4;
	// printf("size = %d\n", size);
	gen->player.img = mlx_new_image(mlx, size, size);
	gen->player.dir = cmap->dir;
	gen->player.x = cmap->x_start + 0.5;
	gen->player.y = cmap->y_start + 0.5;
	gen->txtrs = cmap->txtrs;
	init_horiz_plane(gen);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
				mlx_put_pixel(gen->player.img, i, j, 0xFF00FFFF);
	mlx_image_to_window(gen->mlx, gen->player.img, gen->player.x * gen->sq_size, gen->player.y * gen->sq_size);
	// printf("player.x = %f, player.y = %f\n", gen->player.x, gen->player.y);
	// printf("xpos = %f, ypos = %f\n", gen->player.x * gen->sq_size, gen->player.y * gen->sq_size);
	mlx_set_instance_depth(&gen->player.img->instances[0], 3);
}