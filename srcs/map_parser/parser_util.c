/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 21:00:06 by dyeboa        ########   odam.nl         */
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

//colors	= F:2, C:3
//textures 	= NO:11, SO:12, WE:14, EA:20
//combined 	= 57; no other possibilty to get 57.
int	type_value(char *word)
{
	int	type;

	type = 0;
	if (!strcmp(word, "F"))
		type = 2;
	else if (!strcmp(word, "C"))
		type = 3;
	else if (!strcmp(word, "NO"))
		type = 11;
	else if (!strcmp(word, "SO"))
		type = 12;
	else if (!strcmp(word, "WE"))
		type = 14;
	else if (!strcmp(word, "EA"))
		type = 20;
	else
		error_message("Weird bug, countmap()");
	return (type);
}

void	check_width_height(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		start;

	start = 0;
	fd = open_file(file);
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
	map->map = (char **)malloc(sizeof(char *) * map->y_max);
	if (!map->map)
		error_message("Malloc map->map");
	while (i < map->y_max)
	{
		map->map[i] = malloc(sizeof(char) * map->x_max + 1);
		if (!map->map[i])
			error_message("Malloc map->map[y]");
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
