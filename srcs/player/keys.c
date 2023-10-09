/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:34 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 22:28:58 by dyeboa        ########   odam.nl         */
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
	if (!is_walkable(gen->map[(int)(player->y)][(int)(player->x + (player->dir_x * move))]))
		return ;
	if (!is_walkable(gen->map[(int)(player->y + player->dir_y * move)][(int)(player->x)]))
		return ;
	player->x += (player->dir_x * move);
	player->y += (player->dir_y * move);
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
	if (!is_walkable(gen->map[(int)(player->y)][(int)(player->x - (player->dir_x * move))]))
		return ;
	if (!is_walkable(gen->map[(int)(player->y - player->dir_y * move)][(int)(player->x)]))
		return ;
	player->x -= (player->dir_x * move);
	player->y -= (player->dir_y * move);
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
	if (!is_walkable(gen->map[(int)(player->y + (player->dir_x * move))][(int)(player->x)]))
		return ;
	if (!is_walkable(gen->map[(int)(player->y)][(int)(player->x - player->dir_y * move)]))
		return ;
	player->x -= (player->dir_y * move);
	player->y += (player->dir_x * move);
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
	if (!is_walkable(gen->map[(int)(player->y - (player->dir_x * move))][(int)(player->x)]))
		return ;
	if (!is_walkable(gen->map[(int)(player->y)][(int)(player->x + player->dir_y * move)]))
		return ;
	player->x += (player->dir_y * move);
	player->y -= (player->dir_x * move);
	player->img->instances->x = player->x * gen->sq_size;
	player->img->instances->y = player->y * gen->sq_size;
	gen->draw = 1;
}
