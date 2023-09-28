/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:33:04 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/27 16:14:07 by dyeboa        ########   odam.nl         */
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
	char **array;
	flood_fill(c_map, c_map->map, c_map->startY, c_map->startX);
	print_map(c_map, c_map->map);
	int newx = width_validated_map(c_map);
	int newy = heigth_validated_map(c_map);
	array = c_map->map;
	c_map->map = allocate_map(c_map->map, newy + 2, newx+ 2);
	fill_map(c_map, array, c_map->y_max, c_map->x_max);
	// printf("newx = %d\n", newx);
	printf("newx = %d, newy = %d\n", newx, newy);
	
}

//printf("x_max = %d, x = %d, x_start = %d\n", x_max, x, x_start);
//printf("%c", c_map->map[y][x]);
int		width_validated_map(t_map *c_map)
{
	int y;
	int x;
	int x_start;
	int x_max;

	y = 0;
	x_start = -1;
	x_max = -1;
	while (y < c_map->y_max)
	{
		x = 0;
		x_start = -1;
		while(c_map->map[y][x])
		{
			if (c_map->map[y][x] == '.' || start_position(c_map->map[y][x]) > 0)
			{
				if (c_map->x_start == -1 || c_map->x_start > x)
					c_map->x_start = x;
				if (x_start == -1)
					x_start = x;
				if (x_max < (x - x_start) || x_max == -1)
					x_max = x + 1 - x_start;
			}
			x++;
		}
		y++;
	}
	return (x_max);
}

int	heigth_validated_map(t_map *c_map)
{
	int y;
	int x;
	int y_max;
	
	y = 0;
	y_max = 0;
	c_map->y_start = -1;
	while (y < c_map->y_max)
	{
		x = 0;
		while (c_map->map[y][x])
		{
			if (c_map->map[y][x] == '.')
			{
				if (c_map->y_start == -1)
					c_map->y_start = y;
				y_max++;
				break;
			}
			x++;
		}
		y++;
	}
	return (y_max);
}

void	fill_map(t_map *c_map, char **old_map, int ymax, int xmax)
{
	int y;
	int x;
	int posy;
	int posx;
	int written;


	y = 0;
	x = 0;
	posy = 0;
	posx = 0;
	while (old_map[y])
	{
		written = 0;
		x = 0;
		while (old_map[y][x])
		{
			
			if (y >= (c_map->y_start - 1) && y < c_map->y_start + ymax)
			{
				if (x == 0)
					printf("y: %d > %d && %d > %d + %d\n", y, (c_map->y_start - 1), y, c_map->y_start, ymax);
				if (x == 0)
					printf("x: %d > %d && %d > %d\n", x, (c_map->x_start - 1), x, c_map->x_start + xmax);
				if (x > c_map->x_start - 1 && x < c_map->x_start + xmax)
				{
					
					
					// printf("Lijn kopieren, y;%d ystart: %d, xstart %d\n", y, c_map->y_start, c_map->x_start);
					c_map->map[posy][posx] = old_map[y][x];
					posx++;
					written = 1;
				}
			}
			x++;
		}
		if (written == 1)
			posy++;
		
		// ymax--;
		y++;
	}
	if (written == 1)
		printf("Lijn kopieren, y;%d ystart: %d, xstart %d\n", y, c_map->y_start, c_map->x_start);
	printf("Lijn kopieren, y;%d ystart: %d, xstart %d\n", y, c_map->y_start, c_map->x_start);
	return ;
	old_map++;
	ymax++;
	xmax++;
}
