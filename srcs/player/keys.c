/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:34 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/08 22:01:13 by daaf          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "cub3d.h"

void	walk_forwards(t_gen *gen)
{
	t_player	*player;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	player = &gen->player;
	if (!can_move(gen, 1, 1))// || !can_move(gen, -1, 1) || !can_move(gen, 1, -1))
		return ;
	player->x += (player->dir_x * move);
	player->y += (player->dir_y * move);
	// if (can_move_y(gen, move))
	// 	player->y += (player->dir_y * move);
	// if (can_move_x(gen, move))
	// 	player->x += (player->dir_x * move);
	player->img->instances->x = player->x * gen->sq_size;
	player->img->instances->y = player->y * gen->sq_size;
	gen->draw = 1;
}

void	walk_backwards(t_gen *gen)
{
	t_player	*player;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	player = &gen->player;
	if (!can_move(gen, -1, -1))// || !can_move(gen, -1, 1) || !can_move(gen, 1, -1))
		return ;
	player->x -= (player->dir_x * move);
	player->y -= (player->dir_y * move);
	// if (can_move_y(gen, -move))
	// 	player->y -= (player->dir_y * move);
	// if (can_move_x(gen, -move))
	// 	player->x -= (player->dir_x * move);
	player->img->instances->x = player->x * gen->sq_size;
	player->img->instances->y = player->y * gen->sq_size;
	gen->draw = 1;
}

void	walk_left(t_gen *gen)
{
	t_player	*player;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	player = &gen->player;
	if (!can_move(gen, -1, 1))// || !can_move(gen, 1, 1) || !can_move(gen, -1, -1))
		return ;
	player->x -= (player->dir_y * move);
	player->y += (player->dir_x * move);
	// if (can_move_y(gen, move))
	// 	player->y += (player->dir_x * move);
	// if (can_move_x(gen, -move))
	// 	player->x += -(player->dir_y * move);
	player->img->instances->x = player->x * gen->sq_size;
	player->img->instances->y = player->y * gen->sq_size;
	gen->draw = 1;
}

void	walk_right(t_gen *gen)
{
	t_player	*player;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	player = &gen->player;
	if (!can_move(gen, 1, -1))// || !can_move(gen, 1, 1) || !can_move(gen, -1, -1))
		return ;
	player->x += (player->dir_y * move);
	player->y -= (player->dir_x * move);
	// if (can_move_y(gen, -move))
	// 	player->y += -(player->dir_x * move);
	// if (can_move_x(gen, move))
	// 	player->x += (player->dir_y * move);
	player->img->instances->x = player->x * gen->sq_size;
	player->img->instances->y = player->y * gen->sq_size;
	gen->draw = 1;
}
