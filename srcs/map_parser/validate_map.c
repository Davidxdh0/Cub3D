/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:33:04 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/24 01:32:16 by daaf          ########   odam.nl         */
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
	arr[y][x] = '.';
}

void	flood_fill(const t_map *c_map, char **map, int y, int x)
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
void	validate_map(const t_map *c_map)
{
	flood_fill(c_map, c_map->map, c_map->startY, c_map->startX);
}