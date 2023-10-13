/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 20:17:39 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 17:25:30 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_escape(t_gen *gen)
{
	free_textures(gen);
	ft_free_arr(gen->map);
	mlx_close_window(gen->mlx);
	mlx_terminate(gen->mlx);
	exit(EXIT_SUCCESS);
}

void	rotate_left(t_gen *gen)
{
	double		old_dir;
	double		old_plane;
	double		rot;
	t_player	*player;

	player = &gen->player;
	rot = gen->mlx->delta_time * 3.0;
	old_dir = player->dir_x;
	old_plane = player->plane_x;
	player->dir_x = player->dir_x * cos(-rot) \
	- player->dir_y * sin(-rot);
	player->dir_y = old_dir * sin(-rot) \
	+ player->dir_y * cos(-rot);
	player->plane_x = player->plane_x * cos(-rot) \
	- player->plane_y * sin(-rot);
	player->plane_y = old_plane * sin(-rot) \
	+ player->plane_y * cos(-rot);
	gen->draw = 1;
}

void	rotate_right(t_gen *gen)
{
	double		old_dir;
	double		old_plane;
	double		rot;
	t_player	*player;

	player = &gen->player;
	rot = gen->mlx->delta_time * 3.0;
	old_dir = player->dir_x;
	old_plane = player->plane_x;
	player->dir_x = player->dir_x * cos(rot) \
	- player->dir_y * sin(rot);
	player->dir_y = old_dir * sin(rot) \
	+ player->dir_y * cos(rot);
	player->plane_x = player->plane_x * cos(rot) \
	- player->plane_y * sin(rot);
	player->plane_y = old_plane * sin(rot) \
	+ player->plane_y * cos(rot);
	gen->draw = 1;
}
