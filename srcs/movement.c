/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/24 14:25:19 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	walk(mlx_keydata_t data, t_gen *gen)
{
	if (data.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirY * 0.1;
	}
	else if (data.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirY * -0.1;
	}
	else if (data.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirX * 0.1;
	}
	else if (data.key == MLX_KEY_D && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))// && can_move())
	{
		gen->player.x += gen->player.dirX * -0.1;
	}
}

void	rotate(mlx_keydata_t data, t_gen *gen)
{
	// if (data.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	// else if (data.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	// else if (data.key == MLX_KEY_UP && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	// else if (data.key == MLX_KEY_DOWN && (key.action == MLX_PRESS || key.action  == MLX_REPEAT))
	// {
	// 	// do something
	// }
	(void)data;
	(void)gen;
}

void	movement(mlx_keydata_t data, void *param)
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
}