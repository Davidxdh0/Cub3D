/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 21:04:46 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 21:13:45 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_textures(char *line, t_map *map, char *word)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split(line, ' ');
	if (words == NULL || !words[0])
		error_message("parse_textures went wrong");
	while (words[i])
		i++;
	if (i != 2)
		error_message("parse_textures went wrong");
	words[1][ft_strlen(words[1]) - 1] = '\0';
	i = open_file(words[1]);
	close(i);
	if (!strcmp(words[0], "NO") && map->txtrs->NO == NULL)
		map->txtrs->NO = words[1];
	else if (!strcmp(words[0], "SO") && map->txtrs->SO == NULL)
		map->txtrs->SO = words[1];
	else if (!strcmp(words[0], "WE") && map->txtrs->WE == NULL)
		map->txtrs->WE = words[1];
	else if (!strcmp(words[0], "EA") && map->txtrs->EA == NULL)
		map->txtrs->EA = words[1];
	else
		error_message("parse_textures went wrong");
	ft_free_arr(words);
	return (type_value(word));
}

int	parse_colors(char *line, t_map *c_map, char *word)
{
	int		i;
	int		number;
	char	**colors;
	char	**words;

	i = 0;
	number = 0;
	line[ft_strlen(line)-1] = '\0';
	words = ft_split(line, ' ');
	if (words == NULL || !words[0])
		error_message("parse_textures went wrong");
	while (words[i])
		i++;
	if (i != 2)
		error_message("parseColours not two words");
	colors = ft_split(words[1], ',');
	i = 0;
	while (colors[i])
		i++;
	if (i != 3)
		error_message("parse_colors values not three words");
	i = 0;
	while (colors[i])
	{
		number = ft_atoi(colors[i]);
		if (number < 0 || number > 255)
			error_message("parse_colors value < 0 || > 255");
		i++;
	}
	if (!strcmp(words[0], "F"))
		c_map->txtrs->F = words[1];
	else if (!strcmp(words[0], "C"))
		c_map->txtrs->C = words[1];
	ft_free_arr(words);
	ft_free_arr(colors);
	return (type_value(word));
}

// 1 " " n s w e
int	start_position(char c)
{
	if (c == 'N')
		return (1);
	else if (c == 'S')
		return (2);
	else if (c == 'E')
		return (3);
	else if (c == 'D')
		return (4);
	else
		return (0);
}

void	parse_map(char *str, t_map *c_map, int y)
{
	int	i;

	i = 0;
	if (y < c_map->y_max - 1)
		str[ft_strlen(str) - 1] = '\0';
	while (str[i] != '\0' && (str[i] == '1' || str[i] == '0' || str[i] == \
	' ' || str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'D'))
	{
		if (start_position(str[i]))
		{
			if (c_map->startY == -1)
			{
				c_map->startX = i;
				c_map->startY = y;
			}
			else
				error_message("Multiple starting positions");
		}
		c_map->map[y][i] = str[i];
		i++;
	}
	c_map->map[y][i] = '\0';
	if (str[i])
		error_message("Map contains different values");
}

int	open_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_message("File can't be opened");
	return (fd);
}

//colors f 2 , c 3
//textures no 11, so 12, we 14, ea 20
void	parse_line(char *line, t_map *map)
{
	char		*word;
	static int	map_bool = 0;
	static int	colors = 0;
	static int	textures = 0;

	if (line == NULL)
		error_message("Empty file");
	if (line[0] == '\n')
		return ;
	word = get_first_word(line);
	if (word && (!strcmp(word, "F") || !strcmp(word, "C")) && map_bool == 0)
		colors += parse_colors(line, map, word);
	else if (word && (!strcmp(word, "NO") || !strcmp(word, "SO") || \
		!strcmp(word, "WE") || !strcmp(word, "EA")) \
		&& map_bool == 0)
		textures += parse_textures(line, map, word);
	else if (colors == 5 && textures == 57)
	{
		parse_map(line, map, map_bool);
		map_bool++;
	}
	else
		error_message("Incorrect Textures or Colors");
	if (word)
		free(word);
}

void	parser(char *file, t_map *c_map)
{
	int		fd;
	char	*line;

	check_width_height(file, c_map);
	allocate_map(c_map);
	fd = open_file(file);
	line = get_next_line(fd);
	parse_line(line, c_map);
	while (line && line != NULL)
	{
		parse_line(line, c_map);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (c_map->startX == -1)
		error_message("No starting positions found");
	close (fd);
}
