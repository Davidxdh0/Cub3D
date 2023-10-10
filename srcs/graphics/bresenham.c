/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bresenham.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 20:51:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/10 11:59:06 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	bres_loop(t_gen *gen, t_vector *cur, t_vector *end, t_vector sign)
// {
// 	int		error[2];
// 	t_vector	delta;

// 	delta.x = abs((int)end->x - (int)cur->x);
// 	delta.y = -abs((int)end->y - (int)cur->y);
// 	error[0] = (int)delta.x - (int)delta.y;
// 	(void)cur;
// 	(void)end;
// 	(void)sign;
// 	(void)gen;
// 	(void)error;
// 	while (1)
// 	{
// 		if ((int)cur->x < WIDTH && (int)cur->x >= 0 && (int)cur->y >= 0 && (int)cur->y < HEIGHT)
// 			mlx_put_pixel(gen->minimap, (int)cur->x, (int)cur->y, 0xFF0000FF);
// 		printf("cur.x: %f, end.x: %f, cur.y: %f, end.y: %f\n", cur->x, end->x, cur->y, end->y);
// 		if ((int)cur->x == (int)end->x && (int)cur->y == (int)end->y)
// 			break ;
// 		error[1] = error[0] * 2;
// 		if (error[1] >= delta.y)
// 		{
// 			error[0] += delta.y;
// 			cur->x += sign.x;
// 		}
// 		if (error[1] <= delta.x)
// 		{
// 			error[0] += delta.x;
// 			cur->y += sign.y;
// 		}
// 	}
// }

// void	bresenham(t_gen *gen, t_vector *start, t_vector *end)
// {
// 	t_vector	sign;

// 	sign.x = 1;
// 	sign.y = 1;
// 	if (start->x > end->x)
// 		sign.x = -1;
// 	if (start->y > end->y)
// 		sign.y = -1;
// 	start->x = floor(start->x);
// 	start->y = floor(start->y);
// 	end->x = floor(end->x);
// 	end->y = floor(end->y);
// 	static int i = 0;
// 	if (i++ == 0)
// 	{
// 		printf("start.x: %f, end.x: %f, start.y: %f, end.y: %f\n", start->x, end->x, start->y, end->y);
// 		bres_loop(gen, start, end, sign);
// 	}
// }

void	bresenham(t_gen *gen, int x1, int y1, int x2, int y2)
{
	t_vector	d;
	t_vector	s;
	double		err;
	double		err2;

	d.x = abs(x2 - x1);
	d.y = -abs(y2 - y1);
	s.x = 1;
	if (x1 > x2)
		s.x = -0.1;
	s.y = 1;
	if (y1 > y2)
		s.y = -0.1;
	err = d.x + d.y;
	while (1)
	{
		if (x1 < WIDTH && x1 >= 0 && y1 >= 0 && y1 < HEIGHT)
			mlx_put_pixel(gen->minimap, x1, y1, 0xFF0000FF);
		if (x1 == x2 && y1 == y2)
			break ;
		err2 = 2 * err;
		if (err2 >= d.y)
		{
			err += d.y;
			x1 += s.x;
		}
		if (err2 <= d.x)
		{
			err += d.x;
			y1 += s.y;
		}
	}
}
