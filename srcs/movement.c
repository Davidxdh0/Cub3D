/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/03 12:24:15 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_gen *gen, int speed)
{
	double	x;
	double	y;

	(void)speed;
	x = (int)gen->player.x + (1 * gen->player.dir_x);
	y = (int)gen->player.y + (1 * gen->player.dir_y);
	printf("x: %f, y: %f\n", x, y);
	if (x < 1 || x > gen->width - 2 || y < 1 || y > gen->height - 2)
		return (0);
	if (gen->map[(int)y][(int)x] == '1')
		return (0);
	return (1);
}

void	movement(void *param)
{
	double	move;
	t_gen	*gen;

	gen = (t_gen *)param;
	move = gen->mlx->delta_time * 5.0;
	if (mlx_is_key_down(gen->mlx, MLX_KEY_ESCAPE))
		close_escape(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_W) && can_move(gen, move) == 1)
		walk_forwards(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_S) && can_move(gen, move) == 1)
		walk_backwards(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_A) && can_move(gen, move) == 1)
		walk_right(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D) && can_move(gen, move) == 1)
		walk_left(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_LEFT))
		rotate_right(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_RIGHT))
		rotate_left(gen);
	if (gen->draw == 1)
	{
		render_screen(gen);
		gen->draw = 0;
	}
}

// void	scrolling(void *param)
// {
// 	t_gen	*gen;
// 	double x;
// 	double y;
// 	gen = (t_gen *)param;
// 	if (mlx_scroll_hook(gen->mlx, MLX_KEY_ESCAPE))
// 		close_escape(gen);
// }