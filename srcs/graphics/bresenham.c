/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bresenham.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 20:51:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 14:05:02 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"

static void	bres_loop(t_gen *gen, t_bres bres, int *pos, int *line)
{
	while (1)
	{
		if (pos[0] < WIDTH && pos[0] >= 0 && pos[1] >= 0 && pos[1] < HEIGHT)
			mlx_put_pixel(gen->minimap, pos[0], pos[1], 0xFF0000FF);
		if (pos[0] == line[0] && pos[1] == line[1])
			break ;
		bres.err2 = 2 * bres.err;
		if (bres.err2 >= bres.dy)
		{
			bres.err += bres.dy;
			pos[0] += bres.sx;
		}
		if (bres.err2 <= bres.dx)
		{
			bres.err += bres.dx;
			pos[1] += bres.sy;
		}
	}
}

void	bresenham(t_gen *gen, int *pos, int *line)
{
	t_bres	bres;

	bres.dx = abs(line[0] - pos[0]);
	bres.dy = -abs(line[1] - pos[1]);
	bres.sx = 1;
	bres.sy = 1;
	if (pos[0] > line[0])
		bres.sx = -0.1;
	if (pos[1] > line[1])
		bres.sy = -0.1;
	bres.err = bres.dx + bres.dy;
	bres_loop(gen, bres, pos, line);
}
