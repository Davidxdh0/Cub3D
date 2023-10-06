/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bresenham.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 20:51:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/06 20:51:56 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bres_loop(t_gen *gen, t_vector cur, t_vector end, t_vector sign)
{
	float		error[2];
	t_vector	delta;

	delta.x = abs((int)end.x - (int)cur.x);
	delta.y = abs((int)end.y - (int)cur.y);
	error[0] = delta.x - delta.y;
	while (cur.x != end.x || cur.y != end.y)
	{
		if (cur.x < WIDTH && cur.x >= 0 && cur.y >= 0 && cur.y < HEIGHT)
			mlx_put_pixel(gen->win, cur.x, cur.y, 0xFF0000FF);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void	bresenham(t_gen *gen, t_vector start, t_vector end)
{
	t_vector	sign;

	sign.x = 1;
	sign.y = 1;
	if (start.x > end.x)
		sign.x = -1;
	if (start.y > end.y)
		sign.y = -1;
	bres_loop(gen, start, end, sign);
}

// {
// 	t_vector	d;
// 	t_vector	s;
// 	float		err;
// 	float		err2;

// 	d.x = abs(x2 - x1);
// 	d.y = -abs(y2 - y1);
// 	s.x = 1;
// 	if (x1 > x2)
// 		s.x = -0.1;
// 	s.y = 1;
// 	if (y1 > y2)
// 		s.y = -0.1;
// 	err = d.x + d.y;
// 	while (1)
// 	{
// 		if (x1 < WIDTH && x1 >= 0 && y1 >= 0 && y1 < HEIGHT)
// 			mlx_put_pixel(gen->minimap, x1, y1, 0xFF0000FF);
// 		if (x1 == x2 && y1 == y2)
// 			break ;
// 		err2 = 2 * err;
// 		if (err2 >= d.y)
// 		{
// 			err += d.y;
// 			x1 += s.x;
// 		}
// 		if (err2 <= d.x)
// 		{
// 			err += d.x;
// 			y1 += s.y;
// 		}
// 	}
// }