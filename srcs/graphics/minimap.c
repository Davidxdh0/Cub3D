/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:59:40 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 17:12:10 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "cub3D.h"

static void	draw_square(t_gen *gen, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * gen->sq_size;
	while (i < (x + 1) * gen->sq_size && i < SIZE)
	{
		j = y * gen->sq_size;
		while (j < (y + 1) * gen->sq_size && j < SIZE)
		{
			mlx_put_pixel(gen->minimap, i, j, color);
			++j;
		}
		++i;
	}
}

static void	draw_player(t_gen *gen)
{
	int			x;
	int			y;
	int			size;

	size = gen->sq_size / 2;
	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
			mlx_put_pixel(gen->player.img, x, y, 0xFF00FFFF);
	}
	mlx_image_to_window(gen->mlx, gen->player.img, \
	gen->player.x * gen->sq_size, gen->player.y * gen->sq_size);
	mlx_set_instance_depth(&gen->player.img->instances[0], 2);
}

void	draw_minimap(t_gen *gen)
{
	int			x;
	int			y;
	int			color;

	y = -1;
	while (gen->map[++y])
	{
		x = -1;
		while (gen->map[y][++x])
		{
			if (gen->map[y][x] == '1')
				color = 0xFFFFFF;
			else if (gen->map[y][x] == 'l')
				color = 0x6dfa59;
			else if (gen->map[y][x] == 'c')
				color = 0xed0909;
			else
				color = 0x0000FF;
			draw_square(gen, x, y, color);
		}
	}
	mlx_image_to_window(gen->mlx, gen->minimap, 0, 0);
	mlx_set_instance_depth(&gen->minimap->instances[0], 1);
	draw_player(gen);
}

void	draw_background(t_gen *gen)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = gen->txtrs.ceil;
		else
			color = gen->txtrs.floor;
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(gen->bg, x, y, color);
	}
	mlx_image_to_window(gen->mlx, gen->bg, 0, 0);
	mlx_set_instance_depth(&gen->bg->instances[0], 0);
}

void	draw_vision(t_gen *gen, t_player *player, t_ray ray)
{
	double		line[2];
	double		pos[2];
	int			brs_line[2];
	int			bres_pos[2];

	line[0] = ray.map_x;
	line[1] = ray.map_y;
	if (ray.side == 0)
		line[1] = player->y + ray.walldist * ray.raydir_y;
	else
		line[0] = player->x + ray.walldist * ray.raydir_x;
	line[0] *= gen->sq_size;
	line[1] *= gen->sq_size;
	if (ray.raydir_x < 0 && ray.side == 0)
		line[0] += gen->sq_size;
	if (ray.raydir_y < 0 && ray.side == 1)
		line[1] += gen->sq_size;
	pos[0] = player->x * gen->sq_size + gen->sq_size / 4;
	pos[1] = player->y * gen->sq_size + gen->sq_size / 4;
	brs_line[0] = line[0];
	brs_line[1] = line[1];
	bres_pos[0] = pos[0];
	bres_pos[1] = pos[1];
	bresenham(gen, bres_pos, brs_line);
}
