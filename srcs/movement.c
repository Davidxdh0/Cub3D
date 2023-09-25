/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/25 11:43:16 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walk(mlx_key_data_t data, t_gen *gen)
{
	if (data.key == MLX_KEY_W && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.y += (gen->player.dirY * SPEED);
		gen->player.img->instances->y += -16;//(gen->player.dirY * -SPEED);
	}
	else if (data.key == MLX_KEY_S && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.y += (gen->player.dirY * -SPEED);
		gen->player.img->instances->y += 16;//(gen->player.dirY * SPEED);
	}
	else if (data.key == MLX_KEY_A && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += (gen->player.dirX * SPEED);
		gen->player.img->instances->x += -16;//(gen->player.dirX * SPEED);
	}
	else if (data.key == MLX_KEY_D && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += (gen->player.dirX * -SPEED);
		gen->player.img->instances->x += 16;//(gen->player.dirX * -SPEED);
	}
	else
		return ;
	printf("x = %f, y = %f\n", gen->player.x, gen->player.y);

}

void	rotate(mlx_key_data_t data, t_gen *gen)
{
	// if (data.key == MLX_KEY_LEFT && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	// else if (data.key == MLX_KEY_RIGHT && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	// else if (data.key == MLX_KEY_UP && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	// else if (data.key == MLX_KEY_DOWN && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	(void)data;
	(void)gen;
}

void	movement(mlx_key_data_t data, void *param)
{
	t_gen	*gen;
	
	gen = (t_gen *)param;
	if (data.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(gen->mlx);
		mlx_terminate(gen->mlx);
		// cleanup and exit
	}
	rotate(data, gen);
	walk(data, gen);
}