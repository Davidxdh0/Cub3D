/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:33:04 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 13:37:28 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// printf("valid_space y:x, %d:%d\n", y, x);
void	valid_space(t_map *c_map, char **arr, int x, int y)
{
	// printf("valid_space y:x, %d:%d\n", y, x);
	// printf("xmax%d ymax%d\n", c_map->x_max, c_map->y_max);
	if ((x == c_map->x_max - 1 || y == c_map->y_max - 1) && arr[y][x] != '1')
		error_exit("No walls at border");
	if ( !arr[y - 1][x] || arr[y - 1][x] == ' ')
		error_exit("No walls at N edge");
	if ( !arr[y + 1][x] || arr[y + 1][x] == ' ')
		error_exit("No walls at S edge");
	if (!arr[y][x - 1] || arr[y][x - 1] == ' ')
		error_exit("No walls at W edge");
	if (!arr[y][x + 1] || arr[y][x + 1] == ' ')
		error_exit("No walls at E edge");
	if ( !arr[y - 1][x - 1] || arr[y - 1][x - 1] == ' ')
		error_exit("No walls at NW edge");
	if (!arr[y - 1][x + 1] || arr[y - 1][x + 1] == ' ')
		error_exit("No walls at NE edge");
	if (!arr[y + 1][x + 1] || arr[y + 1][x + 1] == ' ')
		error_exit("No walls at SE edge");
	if (!arr[y + 1][x - 1] || arr[y + 1][x - 1] == ' ')
		error_exit("No walls at SW edge");
	if (arr[y][x] != 'N' && arr[y][x] != 'E' && \
		arr[y][x] != 'S' && arr[y][x] != 'W')
		arr[y][x] = '.';
}

void	flood_fill(t_map *c_map, char **map, int y, int x)
{
	if (x == 0 || x == c_map->x_max)
		error_exit("No walls at sides border");
	if (y == 0 || y == c_map->y_max)
		error_exit("No walls at north or south border");
	if (map[y][x] == '.')
		return ;
	valid_space(c_map, map, x, y);
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
	if (map[y - 1][x + 1] != '.' && map[y - 1][x + 1] == '0')
		flood_fill(c_map, map, y - 1, x + 1);
	if (map[y + 1][x + 1] != '.' && map[y + 1][x + 1] == '0')
		flood_fill(c_map, map, y + 1, x + 1);
	if (map[y + 1][x - 1] != '.' && map[y + 1][x - 1] == '0')
		flood_fill(c_map, map, y, x + 1);
}

// printf("start[y:x]: %d:%d ", c_map.start_y, c_map.start_x);
// printf("= '%c'\n", c_map.map[c_map.start_y][c_map.start_x]);
// printf("ymax %d, xmax %d\n", newy, newx);
void	validate_map(t_map *c_map)
{
	char	**array;

	flood_fill(c_map, c_map->map, c_map->start_y, c_map->start_x);
	width_validated_map(c_map);
	heigth_validated_map(c_map);
	array = c_map->map;
	c_map->y_max += 2;
	c_map->x_max += 2;
	c_map->map = allocate_map(c_map->map, c_map->y_max, c_map->x_max);
	fill_map(c_map, array, c_map->y_max - 2, c_map->x_max - 2);
	find_new_start_pos(c_map);
	ft_free_arr(array);
}

void	width_validated_map(t_map *c_map)
{
	int	y;
	int	x;
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
			if (c_map->map[y][x] == '.' || start_position(c_map->map[y][x]))
			{
				if (c_map->x_start == -1 || c_map->x_start > x)
					c_map->x_start = x;
				if (x_start > x || x_start == -1)
					x_start = x;
				if (x_max < (x + 1 - x_start) || x_max == -1)
				{
					x_max = x + 1 - x_start;
				}
			}
			x++;
		}
		y++;
	}
	// x_max++;
	//printf("x_start: %d, cmap->x_start: %d\n", x_start, c_map->x_start);
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
			if (c_map->map[y][x] == '.' || start_position(c_map->map[y][x]))
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

// 	printf("y: %d > %d && %d > %d + %d\n", y, (c_map->y_start - 1), y, c_map->y_start, ymax);
// 	printf("x: %d > %d && %d > %d\n", x, (c_map->x_start - 1), x, c_map->x_start + xmax);
//	printf("Lijn kopieren, y;%d ystart: %d, xstart %d\n", y, c_map->y_start, c_map->x_start);
void	fill_map(t_map *c_map, char **old_map, int ymax, int xmax)
{
	int	y;
	int	x;
	int	posy;
	int	posx;

	y = -1;
	posy = 0;
	while (old_map[++y] && c_map->map[posy])
	{
		x = -1;
		posx = -1;
		while (old_map[y][++x])
		{
			if (y >= (c_map->y_start - 1) && y <= c_map->y_start + ymax \
			&& x >= c_map->x_start - 1 && x < c_map->x_start + xmax + 1)
			{
				if (old_map[y][x] == '.')
					c_map->map[posy][++posx] = '0';
				else
					c_map->map[posy][++posx] = old_map[y][x];
			}
		}
		if (!old_map[y][x])
			c_map->map[posy][++posx] = '\0';
		if (posx > 0)
			posy++;
	}
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
			if (start_position(map->map[y][x]))
			{
				map->x_start = x;
				map->y_start = y;
				map->dir = start_position(map->map[y][x]);
				map->map[y][x] = '0';
				break ;
			}
			x++;
		}
	}
}
