/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/24 17:14:26 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walk(mlx_key_data_t data, t_gen *gen)
{
	if (data.key == MLX_KEY_W && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirY * 0.1;
		gen->player.img->instances->y += -0.1;
	}
	else if (data.key == MLX_KEY_S && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirY * -0.1;
		gen->player.img->instances->y -= 0.1;
	}
	else if (data.key == MLX_KEY_A && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirX * 0.1;
		gen->player.img->instances->x += -0.1;
	}
	else if (data.key == MLX_KEY_D && (data.action == MLX_PRESS || data.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirX * -0.1;
		gen->player.img->instances->x -= -0.1;
	}
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
	walk(data, gen);
	rotate(data, gen);
	printf("x = %f, y = %f\n", gen->player.x, gen->player.y);
}