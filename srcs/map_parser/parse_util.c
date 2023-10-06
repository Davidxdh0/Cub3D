/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/06 21:12:17 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	map->y_max -= start;
	free(line);
	close(fd);
}

char	**allocate_map(char **map, int y, int x)
{
	int	i;

	if (y == -1 || x == -1)
		error_exit("Invalid ymax or xmax");
	map = (char **)ft_calloc(sizeof(char *), (y + 1));
	if (!map)
		error_exit("Malloc map");
	i = 0;
	while (i < y)
	{
		map[i] = ft_calloc(sizeof(char), (x + 2));
		if (!map[i])
			error_exit("Malloc map[y]");
		i++;
	}
	map[i] = NULL;
	return (map);
}

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	get_colors(t_map *map, char **words, char **colors)
{
	int		i;
	int		number;
	int32_t	rgb;
	int		arr[3];

	i = 0;
	rgb = 0;
	while (colors[i])
	{
		number = ft_atoi(colors[i]);
		if (number < 0 || number > 255)
			error_free("Invalid color value", map);
		arr[i] = number;
		i++;
	}
	rgb = get_rgba(arr[0], arr[1], arr[2], 255);
	if (!strcmp(words[0], "F"))
		map->txtrs.floor = rgb;
	else if (!strcmp(words[0], "C"))
		map->txtrs.ceil = rgb;
}
