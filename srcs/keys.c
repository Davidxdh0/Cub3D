/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:34 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/02 12:37:35 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_escape(mlx_key_data_t data, t_gen *gen)
{
	mlx_close_window(gen->mlx);
	mlx_terminate(gen->mlx);
	exit(0);
}

void	rotate_right(mlx_key_data_t data, t_gen *gen)
{
	double		old_dir;
	double		old_plane;
	double		rot;
	t_player	*player;

	player = &gen->player;
	rot = gen->mlx->delta_time * 5.0;
	old_dir = player->dir_x;
	old_plane = player->plane_x;
	player->dir_x = player->dir_x * cos(-rot) - player->dir_y * sin(-rot);
	player->dir_y = old_dir * sin(-rot) + player->dir_y * cos(-rot);
	player->plane_x = player->plane_x * cos(-rot) - player->plane_y * sin(-rot);
	player->plane_y = old_plane * sin(-rot) + player->plane_y * cos(-rot);
}

void	rotate_left(mlx_key_data_t data, t_gen *gen)
{
	double		old_dir;
	double		old_plane;
	double		rot;
	t_player	*player;

	player = &gen->player;
	rot = gen->mlx->delta_time * 5.0;
	old_dir = player->dir_x;
	old_plane = player->plane_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir * sin(rot) + player->dir_y * cos(rot);
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane * sin(rot) + player->plane_y * cos(rot);
}

void	walk_forwards(mlx_key_data_t data, t_gen *gen, double move)
{
	gen->player.y += (gen->player.dir_y * move);
	gen->player.x += (gen->player.dir_x * move);
	gen->player.img->instances->x = gen->player.x * SIZE / 4;
	gen->player.img->instances->y = gen->player.y * SIZE / 4;
}

void	Walk_backwards(mlx_key_data_t data, t_gen *gen, double move)
{
	gen->player.y -= (gen->player.dir_y * move);
	gen->player.x -= (gen->player.dir_x * move);
	gen->player.img->instances->x = gen->player.x * SIZE / 4;
	gen->player.img->instances->y = gen->player.y * SIZE / 4;
}

void	walk_left(mlx_key_data_t data, t_gen *gen, double move)
{
	gen->player.y += (gen->player.dir_x * move);
	gen->player.x += -(gen->player.dir_y * move);
	gen->player.img->instances->x = gen->player.x * SIZE / 4;
	gen->player.img->instances->y = gen->player.y * SIZE / 4;
}

void	walk_right(mlx_key_data_t data, t_gen *gen, double move)
{
	gen->player.y += -(gen->player.dir_x * move);
	gen->player.x += (gen->player.dir_y * move);
	gen->player.img->instances->x = gen->player.x * SIZE / 4;
	gen->player.img->instances->y = gen->player.y * SIZE / 4;
}