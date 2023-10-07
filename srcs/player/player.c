/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 14:51:52 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/06 23:30:43 by bfranco       ########   odam.nl         */
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
	gen->player.img = mlx_new_image(mlx, size, size);
	if (!gen->player.img)
	{
		free(cmap);
		ft_free_arr(gen->map);
		error_exit("Failed to create player image");
	}
	gen->player.dir = cmap->dir;
	gen->player.x = cmap->x_start + 0.5;
	gen->player.y = cmap->y_start + 0.5;
	gen->txtrs = cmap->txtrs;
	init_horiz_plane(gen);
}
