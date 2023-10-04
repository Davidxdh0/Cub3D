/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/04 09:13:03 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	can_move(t_gen *gen, int speed)
// {
// 	double	x;
// 	double	y;

// 	(void)speed;
// 	x = (int)gen->player.x + (0.5 * gen->player.dir_x);
// 	y = (int)gen->player.y + (0.5 * gen->player.dir_y);
// 	// printf("x: %f, y: %f\n", x, y);
// 	if (x < 1 || x > gen->width - 1 || y < 1 || y > gen->height - 1)
// 		return (0);
// 	// if (gen->map[(int)y + 1][(int)x + 1] == '1')
// 	// 	return (0);
// 	// if (gen->map[(int)y + 1][(int)x - 1] == '1')
// 	// 	return (0);
// 	// if (gen->map[(int)y - 1][(int)x - 1] == '1')
// 	// 	return (0);
// 	// if (gen->map[(int)y - 1][(int)x + 1] == '1')
// 	// 	return (0);
// 	return (1);
// }

int	can_move_x(t_gen *gen, int speed)
{
	double	x;
	double	y;
	double diff;

	(void)speed;
	x = (gen->player.x) + (0.5 * gen->player.dir_x);
	y = (gen->player.y);
	// printf("move x = x: %f, y: %f, int x %d, int y %d\n", x, y, (int)round(x), (int)round(y));
	if (x < 1 || x > gen->width - 1.5 || y < 1 || y > gen->height - 1)
		return (0);
	if (gen->map[(int)round(y)][(int)round(x)] == '1' || gen->map[(int)round(y)][(int)round(x - 1)] == '1' \
		|| gen->map[(int)round(y - 1)][(int)round(x)] == '1' || gen->map[(int)round(y - 1)][(int)round(x) - 1] == '1')
	{
		// printf("wallx: %d %d ", (int)round(y), (int)round(x));
		diff = round(x);
		if (fabs(x - diff) < 0.5 )//&& fabs(diff - x) < 0.3)
		{
			// printf("diff2 X %f, %f", fabs(x - diff), fabs(diff - x));
			return (0);
		}
	}
	return (1);
}

int	can_move_y(t_gen *gen, int speed)
{
	double	x;
	double	y;
	double diff;
	(void)speed;
	x = (gen->player.x);
	y = (gen->player.y) + (0.5 * gen->player.dir_y);
	// printf("move y = x: %f, y: %f, int x %d, int y %f inty %d, height %d\n", x, y, (int)round(x), round(y), (int)round(y),  gen->height);
	if (x < 1 || x > gen->width - 1.5 || y < 1 || y > gen->height - 1)
	{
		// printf("move y -> side\n");
		return (0);
	}
	if (gen->map[(int)round(y)][(int)round(x)] == '1' || gen->map[(int)round(y - 1)][(int)round(x)] == '1' \
		|| gen->map[(int)round(y)][(int)round(x - 1)] == '1' || gen->map[(int)round(y - 1)][(int)round(x - 1)] == '1')
	{
		// printf("wally: %d %d \n", (int)round(y), (int)round(x));
		diff = round(y );
		double diff2 = fabs(y - diff);
		if (diff2 < 0.5 )//&& fabs(diff - y) < 0.5)
		{
			// printf("diff2 Y %f - %f = %f - round %f\n",y, diff, diff2, round(y - 1));
			return (0);
		}
	}
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
	if (mlx_is_key_down(gen->mlx, MLX_KEY_W))// && can_move(gen, move) == 1)
		walk_forwards(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_S))// && can_move(gen, move) == 1)
		walk_backwards(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_A))// && can_move(gen, move) == 1)
		walk_right(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D))// && can_move(gen, move) == 1)
		walk_left(gen, move);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_LEFT))
		rotate_right(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_RIGHT))
		rotate_left(gen);
	if (gen->draw == 1)
	{
		// printf("x: %f, y: %f xmax: %d,  ymax %d\n", gen->player.x, gen->player.y, gen->width, gen->height);
		// printf("x: %f, y: %f\n", gen->player.x * gen->sq_size, gen->player.y * gen->sq_size);
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