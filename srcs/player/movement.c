/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 13:31:30 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/07 20:22:40 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "graphics.h"
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
	double	diff;

	x = (gen->player.x) + (speed * gen->player.dir_x);
	y = (gen->player.y);
	if (x < 1 || x > gen->width - 1.5 || y < 1 || y > gen->height - 1)
		return (0);
	//if (gen->map[(int)round(y)][(int)round(x)] == '1' 
	// || gen->map[(int)round(y)][(int)round(x - 1)] == '1' 
	// || gen->map[(int)round(y - 1)][(int)round(x)] == '1' 
	// || gen->map[(int)round(y - 1)][(int)round(x) - 1] == '1')
	if (gen->map[(int)round(y)][(int)round(x)] == '1')
	{
		diff = round(x);
		if (fabs(x - diff) < 0.5)
			return (0);
	}
	return (1);
}

int	can_move_y(t_gen *gen, int speed)
{
	double	x;
	double	y;
	double	diff;

	x = (gen->player.x);
	y = (gen->player.y) + (speed * gen->player.dir_y);
	if (x < 1.5 || x > gen->width - 1.5 || y < 1.5 || y > gen->height - 1)
		return (0);
	//if (gen->map[(int)round(y)][(int)round(x)] == '1') 
	// || gen->map[(int)round(y - 1)][(int)round(x)] == '1' 
	// || gen->map[(int)round(y)][(int)round(x - 1)] == '1' 
	// || gen->map[(int)round(y - 1)][(int)round(x - 1)] == '1')
	if (gen->map[(int)round(y)][(int)round(x)] == '1')
	{
		diff = round(y);
		if (fabs(y - diff) < 0.5)
			return (0);
	}
	return (1);
}

void	movement(void *param)
{
	t_gen	*gen;

	gen = (t_gen *)param;
	if (mlx_is_key_down(gen->mlx, MLX_KEY_ESCAPE))
		close_escape(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_W))
		walk_forwards(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_S))
		walk_backwards(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_A))
		walk_right(gen);
	if (mlx_is_key_down(gen->mlx, MLX_KEY_D))
		walk_left(gen);
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