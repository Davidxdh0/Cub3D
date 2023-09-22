/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 22:48:32 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// printf("i=%zu, start=%zu, str=%s, line=%s", i, start, str, line);
char	*get_first_word(char *line)
{
	char	*str;
	size_t	i;
	size_t	start;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_isdigit(line[i]))
		return (NULL);
	if (line[i] && ft_isalpha(line[i]))
	{
		start = i;
		while (line[i] && ft_isalpha(line[i]))
			i++;
		str = malloc(sizeof(char *) * i - start + 1);
		if (!str)
			return (NULL);
		ft_strlcpy(str, line, i - start + 1);
	}
	else
		str = NULL;
	return (str);
}

//	printf("max_x = %d, max_y = %d\n", map->x_max, map->y_max);
void	check_width_height(t_map *map, int start, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] && ft_isdigit(line[i]))
		{
			if (start == 0)
				start = map->y_max;
			while (line[i])
				i++;
		}
		if (i > map->x_max)
			map->x_max = i - 1;
		map->y_max++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->y_max -= start;
	close(fd);
}

void	allocate_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->y_max == -1 || map->x_max == -1)
		error_exit("No ymax or xmax");
	map->map = (char **)malloc(sizeof(char *) * map->y_max);
	if (!map->map)
		error_exit("Malloc map->map");
	while (i < map->y_max)
	{
		map->map[i] = malloc(sizeof(char) * map->x_max + 1);
		if (!map->map[i])
			error_exit("Malloc map->map[y]");
		i++;
	}
}

void	print_map(const t_map *map, char **array)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while ((int)y < map->y_max && array[y])
	{
		x = 0;
		while (x < ft_strlen(array[y]) && array[y][x])
		{
			printf("%c", array[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	x = 0;
	while ((int)x < map->x_max)
	{
		printf("__");
		x++;
	}
	printf("\n");
	printf("\n");
}
