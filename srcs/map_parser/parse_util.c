/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/02 09:29:34 by dyeboa        ########   odam.nl         */
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
			map->x_max = i;
		map->y_max++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->y_max -= start;
	close(fd);
}

char**	allocate_map(char **map, int y, int x)
{
	int	i;

	if (y == -1 || x == -1)
		error_exit("No ymax or xmax");
	map = (char **)malloc(sizeof(char *) * (y + 1));
	if (!map)
		error_exit("Malloc map");
	i = 0;
	while (i < y)
	{
		map[i] = malloc(sizeof(char) * (x + 1) );
		if (!map[i])
			error_exit("Malloc map[y]");
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	print_map(const t_map *map, char **array)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < map->y_max && array[y])
	{
		x = 0;
		while (array[y][x])
		{
			printf("%c", array[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	x = 0;
	while (x < map->x_max)
	{
		printf("__");
		x++;
	}
	printf("\n");
	printf("\n");
	// printr()
}

int	count_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return (i);
	while (array[i])
		i++;
	return (i);
}