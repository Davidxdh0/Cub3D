/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:34 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 23:28:24 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "cub3d.h"

void	walk_forwards(t_gen *gen)
{
	t_player	*p;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	p = &gen->p;
	if (!is_walkable(gen->map[(int)(p->y)][(int)(p->x + (p->dir_x * move))]))
		return ;
	if (!is_walkable(gen->map[(int)(p->y + p->dir_y * move)][(int)(p->x)]))
		return ;
	p->x += (p->dir_x * move);
	p->y += (p->dir_y * move);
	p->img->instances->x = p->x * gen->sq_size;
	p->img->instances->y = p->y * gen->sq_size;
	gen->draw = 1;
}

void	walk_backwards(t_gen *gen)
{
	t_player	*p;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	p = &gen->p;
	if (!is_walkable(gen->map[(int)(p->y)][(int)(p->x - (p->dir_x * move))]))
		return ;
	if (!is_walkable(gen->map[(int)(p->y - p->dir_y * move)][(int)(p->x)]))
		return ;
	p->x -= (p->dir_x * move);
	p->y -= (p->dir_y * move);
	p->img->instances->x = p->x * gen->sq_size;
	p->img->instances->y = p->y * gen->sq_size;
	gen->draw = 1;
}

void	walk_left(t_gen *gen)
{
	t_player	*p;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	p = &gen->p;
	if (!is_walkable(gen->map[(int)(p->y + (p->dir_x * move))][(int)(p->x)]))
		return ;
	if (!is_walkable(gen->map[(int)(p->y)][(int)(p->x - p->dir_y * move)]))
		return ;
	p->x -= (p->dir_y * move);
	p->y += (p->dir_x * move);
	p->img->instances->x = p->x * gen->sq_size;
	p->img->instances->y = p->y * gen->sq_size;
	gen->draw = 1;
}

void	walk_right(t_gen *gen)
{
	t_player	*p;
	float		move;

	move = gen->mlx->delta_time * 5.0;
	p = &gen->p;
	if (!is_walkable(gen->map[(int)(p->y - (p->dir_x * move))][(int)(p->x)]))
		return ;
	if (!is_walkable(gen->map[(int)(p->y)][(int)(p->x + p->dir_y * move)]))
		return ;
	p->x += (p->dir_y * move);
	p->y -= (p->dir_x * move);
	p->img->instances->x = p->x * gen->sq_size;
	p->img->instances->y = p->y * gen->sq_size;
	gen->draw = 1;
}
