/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/27 11:59:05 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_gen *gen, int speed)
{
	int	x;
	int	y;

	x = (int)(gen->player.x + gen->player.dirX * speed);
	y = (int)(gen->player.y + gen->player.dirY * speed);
	if (x < 1 || x > MAP_WIDTH - 2 || y < 1 || y > MAP_HEIGHT - 2)
		return (0);
	return (1);
}


void	walk(mlx_key_data_t data, t_gen *gen)
{
	double	moveSpeed;
	
	moveSpeed = gen->mlx->delta_time * 5.0;
	if (data.key == MLX_KEY_W && (data.action == MLX_PRESS || data.action  == MLX_REPEAT) && can_move(gen, moveSpeed))
	{
		gen->player.y += (gen->player.dirY * moveSpeed);
		gen->player.x += (gen->player.dirX * moveSpeed);
		// gen->player.img->instances->y = gen->player.y * SIZE / 4;
		// gen->player.img->instances->x = gen->player.x * SIZE / 4;
	}
	else if (data.key == MLX_KEY_S && (data.action == MLX_PRESS || data.action  == MLX_REPEAT) && can_move(gen, moveSpeed))
	{
		gen->player.y -= (gen->player.dirY * moveSpeed);
		gen->player.x -= (gen->player.dirX * moveSpeed);
		// gen->player.img->instances->y = gen->player.y * SIZE / 4;
		// gen->player.img->instances->x = gen->player.x * SIZE / 4;
	}
	else if (data.key == MLX_KEY_A && (data.action == MLX_PRESS || data.action  == MLX_REPEAT) && can_move(gen, moveSpeed))
	{
		gen->player.y += (gen->player.dirX * moveSpeed);
		gen->player.x += -(gen->player.dirY * moveSpeed);
	}
	else if (data.key == MLX_KEY_D && (data.action == MLX_PRESS || data.action  == MLX_REPEAT) && can_move(gen, moveSpeed))
	{
		gen->player.y += -(gen->player.dirX * moveSpeed);
		gen->player.x += (gen->player.dirY * moveSpeed);
	}
	else
		return ;
	// printf("x = %f, y = %f\n", gen->player.x, gen->player.y);

}

void	rotate(mlx_key_data_t data, t_gen *gen)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	rotSpeed = gen->mlx->delta_time * 3.0;
	oldDirX = gen->player.dirX;
	oldPlaneX = gen->player.planeX;
	if (data.key == MLX_KEY_LEFT && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	{
		gen->player.dirX = gen->player.dirX * cos(rotSpeed) - gen->player.dirY * sin(rotSpeed);
		gen->player.dirY = oldDirX * sin(rotSpeed) + gen->player.dirY * cos(rotSpeed);
		gen->player.planeX = gen->player.planeX * cos(rotSpeed) - gen->player.planeY * sin(rotSpeed);
		gen->player.planeY = oldPlaneX * sin(rotSpeed) + gen->player.planeY * cos(rotSpeed);
	}
	else if (data.key == MLX_KEY_RIGHT && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	{
		gen->player.dirX = gen->player.dirX * cos(-rotSpeed) - gen->player.dirY * sin(-rotSpeed);
		gen->player.dirY = oldDirX * sin(-rotSpeed) + gen->player.dirY * cos(-rotSpeed);
		gen->player.planeX = gen->player.planeX * cos(-rotSpeed) - gen->player.planeY * sin(-rotSpeed);
		gen->player.planeY = oldPlaneX * sin(-rotSpeed) + gen->player.planeY * cos(-rotSpeed);
	}
	else if (data.key == MLX_KEY_UP && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	{
		// do something
		return ;
	}
	else if (data.key == MLX_KEY_DOWN && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	{
		// do something
		return ;
	}
	printf("dirx = %f, diry = %f\n", gen->player.dirX , gen->player.dirY);
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