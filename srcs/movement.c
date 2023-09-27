/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/27 16:26:49 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_gen *gen, int speed)
{
	int	x;
	int	y;

	x = (int)(gen->player.x + gen->player.dir_x * speed);
	y = (int)(gen->player.y + gen->player.dir_y * speed);
	if (x < 1 || x > MAP_WIDTH - 2 || y < 1 || y > MAP_HEIGHT - 2)
		return (0);
	return (1);
}

void	walk(mlx_key_data_t data, t_gen *gen)
{
	double	move;

	move = gen->mlx->delta_time * 5.0;
	if (data.key == MLX_KEY_W && (data.action == MLX_PRESS || \
	data.action == MLX_REPEAT) && can_move(gen, move))
	{
		gen->player.y += (gen->player.dir_y * move);
		gen->player.x += (gen->player.dir_x * move);
	}
	else if (data.key == MLX_KEY_S && (data.action == MLX_PRESS || \
	data.action == MLX_REPEAT) && can_move(gen, move))
	{
		gen->player.y -= (gen->player.dir_y * move);
		gen->player.x -= (gen->player.dir_x * move);
	}
	else if (data.key == MLX_KEY_A && (data.action == MLX_PRESS || \
	data.action == MLX_REPEAT) && can_move(gen, move))
	{
		gen->player.y += (gen->player.dir_x * move);
		gen->player.x += -(gen->player.dir_y * move);
	}
	else if (data.key == MLX_KEY_D && (data.action == MLX_PRESS || \
	data.action == MLX_REPEAT) && can_move(gen, move))
	{
		gen->player.y += -(gen->player.dir_x * move);
		gen->player.x += (gen->player.dir_y * move);
	}
}

void	rotate(mlx_key_data_t data, t_gen *gen)
{
	double		old_dir;
	double		old_plane;
	double		rot;
	t_player	*player;

	player = &gen->player;
	rot = gen->mlx->delta_time * 5.0;
	old_dir = player->dir_x;
	old_plane = player->plane_x;
	if (data.key == MLX_KEY_LEFT && (data.action == MLX_PRESS \
	|| data.action == MLX_REPEAT))
	{
		player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
		player->dir_y = old_dir * sin(rot) + player->dir_y * cos(rot);
		player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
		player->plane_y = old_plane * sin(rot) + player->plane_y * cos(rot);
	}
	else if (data.key == MLX_KEY_RIGHT && (data.action == MLX_PRESS \
	|| data.action == MLX_REPEAT))
	{
		player->dir_x = player->dir_x * cos(-rot) - player->dir_y * sin(-rot);
		player->dir_y = old_dir * sin(-rot) + player->dir_y * cos(-rot);
		player->plane_x = player->plane_x * cos(-rot) - player->plane_y * sin(-rot);
		player->plane_y = old_plane * sin(-rot) + player->plane_y * cos(-rot);
	}
}

void	movement(mlx_key_data_t data, void *param)
{
	t_gen	*gen;

	gen = (t_gen *)param;
	if (data.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(gen->mlx);
		mlx_terminate(gen->mlx);
		exit(0);
	}
	rotate(data, gen);
	walk(data, gen);
}
