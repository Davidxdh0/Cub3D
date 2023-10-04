/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_types.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 21:22:16 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/04 13:05:33 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_textures(char *line, t_map *map, char *word)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split(line, ' ');
	if (ft_arrlen(words) != 2)
		error_free("parse_textures went wrong", map);
	words[1][ft_strlen(words[1]) - 1] = '\0';
	i = open_file(words[1]);
	close(i);
	if (!strcmp(words[0], "NO") && map->txtrs.NO == NULL)
		map->txtrs.NO = ft_strdup(words[1]);
	else if (!strcmp(words[0], "SO") && map->txtrs.SO == NULL)
		map->txtrs.SO = ft_strdup(words[1]);
	else if (!strcmp(words[0], "WE") && map->txtrs.WE == NULL)
		map->txtrs.WE = ft_strdup(words[1]);
	else if (!strcmp(words[0], "EA") && map->txtrs.EA == NULL)
		map->txtrs.EA = ft_strdup(words[1]);
	else
		error_free("parse_textures went wrong", map);
	ft_free_arr(words);
	return (type_value(word));
}

// line[ft_strlen(line) - 1] = '\0';
int	parse_colors(char *line, t_map *c_map, char *word)
{
	char	**colors;
	char	**words;

	line[ft_strlen(line) - 1] = '\0';
	words = ft_split(line, ' ');
	if (ft_arrlen(words) != 2)
		error_free("parse_colours not two words", c_map);
	colors = ft_split(words[1], ',');
	if (ft_arrlen(colors) != 3)
		error_free("parse_colors values not three words", c_map);
	get_colors(c_map, words, colors);
	ft_free_arr(words);
	ft_free_arr(colors); 
	return (type_value(word));
}

int	parse_map(char *str, t_map *c_map, int y)
{
	int	i;

	i = 0;
	if (y < c_map->y_max - 1)
		str[ft_strlen(str) - 1] = '\0';
	while (str[i] != '\0' && (str[i] == '1' || str[i] == '0' || \
		str[i] == ' ' || start_position(str[i])))
	{
		if (start_position(str[i]))
		{
			if (c_map->startY == -1)
			{
				c_map->startX = i;
				c_map->startY = y;
			}
			else
				error_free("Multiple starting positions", c_map);
		}
		c_map->map[y][i] = str[i];
		i++;
	}
	c_map->map[y][i] = '\0';
	if (str[i])
		error_free("Map contains different values", c_map);
	return (1);
}

// 1 " " n s w e
char	start_position(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	else
		return (0);
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
	return (type);
}
