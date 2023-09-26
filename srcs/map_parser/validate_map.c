/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:33:04 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/25 15:22:19 by daaf          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// printf("valid_space y:x, %d:%d\n", y, x);
void	valid_space(char **arr, int x, int y)
{
	if (arr[y - 1][x] == ' ' || !arr[y - 1][x])
		error_exit("No walls at N edge");
	if (arr[y + 1][x] == ' ' || !arr[y + 1][x])
		error_exit("No walls at S edge");
	if (arr[y][x - 1] == ' ' || !arr[y][x - 1])
		error_exit("No walls at W edge");
	if (arr[y][x + 1] == ' ' || !arr[y][x + 1])
		error_exit("No walls at E edge");
	if (arr[y - 1][x - 1] == ' ' || !arr[y - 1][x - 1])
		error_exit("No walls at NW edge");
	if (arr[y - 1][x + 1] == ' ' || !arr[y - 1][x + 1])
		error_exit("No walls at NE edge");
	if (arr[y + 1][x + 1] == ' ' || !arr[y + 1][x + 1])
		error_exit("No walls at SE edge");
	if (arr[y + 1][x - 1] == ' ' || !arr[y + 1][x - 1])
		error_exit("No walls at SW edge");
	if (arr[y][x] != 'N' && arr[y][x] != 'E' && \
		arr[y][x] != 'S' && arr[y][x] != 'W')
		arr[y][x] = '.';
}

void	flood_fill(t_map *c_map, char **map, int y, int x)
{
	if (x == 0 || x == c_map->x_max)
		error_exit("No walls at X edge");
	if (y == 0 || y == c_map->y_max)
		error_exit("No walls at Y edge");
	if (map[y][x] == '.')
		return ;
	valid_space(map, x, y);
	if (map[y - 1][x] != '.' && map[y - 1][x] == '0')
		flood_fill(c_map, map, y - 1, x);
	if (map[y + 1][x] != '.' && map[y + 1][x] == '0')
		flood_fill(c_map, map, y + 1, x);
	if (map[y][x - 1] != '.' && map[y][x - 1] == '0')
		flood_fill(c_map, map, y, x - 1);
	if (map[y][x + 1] != '.' && map[y][x + 1] == '0')
		flood_fill(c_map, map, y, x + 1);
	if (map[y - 1][x - 1] != '.' && map[y - 1][x - 1] == '0')
		flood_fill(c_map, map, y - 1, x - 1);
	if (map[y + 1][x + 1] != '.' && map[y + 1][x + 1] == '0')
		flood_fill(c_map, map, y + 1, x + 1);
	if (map[y + 1][x + 1] != '.' && map[y + 1][x + 1] == '0')
		flood_fill(c_map, map, y, x - 1);
	if (map[y + 1][x - 1] != '.' && map[y + 1][x - 1] == '0')
		flood_fill(c_map, map, y, x + 1);
}

// printf("start[y:x]: %d:%d ", c_map.startY, c_map.startX);
// printf("= '%c'\n", c_map.map[c_map.startY][c_map.startX]);
void	validate_map(t_map *c_map)
{
	int newx = 0;
	// int newy = 0;

	flood_fill(c_map, c_map->map, c_map->startY, c_map->startX);
	// newx = width_validated_map(c_map);
	// newy = heigth_validated_map(c_map);
	printf("newx = %d\n", newx);
	// printf("newx = %d, newy = %d\n", newx, newy);
}

int		width_validated_map(t_map *c_map)
{
	int y;
	int x;
	int x_start;
	int x_max;
	
	y = 0;
	x_start = -1;
	x_max = -1;
	while (c_map->map[y])
	{
		x = 0;
		while(c_map->map[y][x])
		{
			if (c_map->map[y][x] == '.')
			{
				if (x_start > x || x_start == -1)
					x_start = x;
				while (c_map->map[y][x] == '.')
					x++;
			}
			if (x_max < x || x_max == -1)
				x_max = x;
			if (c_map->map[y][x])
				x++;
		}
		y++;
	}
	return (x_max);
}

int		heigth_validated_map(t_map *c_map)
{
	int y;
	int x;
	int y_start;
	int y_max;
	
	y = 0;
	y_start = -1;
	y_max = 0;
	while (c_map->map[y] )
	{
		x = 0;
		while (c_map->map[y][x])
		{
			if (c_map->map[y][x] == '.')
			{
				printf("%c", c_map->map[y][x]);
				if (y_start == -1)
					y_start = y;
				y_max++;
				break;
			}
			x++;
		}
		y++;
	}
	return (y_max - y_start);
}