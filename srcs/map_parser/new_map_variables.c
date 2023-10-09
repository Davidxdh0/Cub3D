/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_map_variables.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 13:52:29 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 18:34:19 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	width_validated_map(t_map *c_map, int y, int x)
{
	int	x_start;
	int	x_max;

	y = 0;
	x_start = -1;
	x_max = -1;
	while (y < c_map->y_max)
	{
		x = 0;
		while (c_map->map[y][x])
		{
			if (is_changed(c_map->map[y][x]) || start_pos(c_map->map[y][x]))
			{
				if (c_map->x_start == -1 || c_map->x_start > x)
					c_map->x_start = x;
				if (x_start > x || x_start == -1)
					x_start = x;
				if (x_max < (x + 1 - x_start) || x_max == -1)
					x_max = x + 1 - x_start;
			}
			x++;
		}
		y++;
	}
	c_map->x_max = x_max;
}

void	heigth_validated_map(t_map *c_map)
{
	int	y;
	int	x;
	int	y_max;

	y = 0;
	y_max = 0;
	c_map->y_start = -1;
	while (y < c_map->y_max)
	{
		x = 0;
		while (c_map->map[y][x])
		{
			if (is_changed(c_map->map[y][x]) || start_pos(c_map->map[y][x]))
			{
				if (c_map->y_start == -1)
					c_map->y_start = y;
				y_max++;
				break ;
			}
			x++;
		}
		y++;
	}
	c_map->y_max = y_max;
}

void	find_new_start_pos(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (map->map[++y])
	{
		x = 0;
		while (map->map[y][x] && x < map->x_max)
		{
			if (start_pos(map->map[y][x]))
			{
				map->x_start = x;
				map->y_start = y;
				map->dir = start_pos(map->map[y][x]);
				map->map[y][x] = '0';
				break ;
			}
			x++;
		}
	}
}
