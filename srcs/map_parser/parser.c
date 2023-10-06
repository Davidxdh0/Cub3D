/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 21:04:46 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/06 21:07:36 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//colors f 2 , c 3
//textures no 11, so 12, we 14, ea 20
void	parse_line(char *line, t_map *map)
{
	char		*word;
	static int	map_bool = 0;
	static int	colors = 0;
	static int	textures = 0;

	if (line[0] == '\n')
		return ;
	word = get_first_word(line);
	if (word && (!ft_strncmp(word, "F", 2) \
	|| !ft_strncmp(word, "C", 2)) && !map_bool)
		colors += parse_colors(line, map, word);
	else if (word && (!ft_strncmp(word, "NO", 3) || !ft_strncmp(word, "SO", 3) \
	|| !ft_strncmp(word, "WE", 3) || !ft_strncmp(word, "EA", 3)) && !map_bool)
		textures += parse_textures(line, map, word);
	else if (colors == 5 && textures == 57)
		map_bool += parse_map(line, map, map_bool);
	else
		error_free("Invalid Textures or Colors", map);
	if (word)
		free(word);
}

void	parser(char *file, t_map *c_map)
{
	int		fd;
	char	*line;

	check_extension(file);
	fd = open_file(file);
	check_width_height(c_map, 0, fd);
	c_map->map = allocate_map(c_map->map, c_map->y_max, c_map->x_max);
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
	close (fd);
	if (c_map->start_x == -1)
		error_free("No starting positions found", c_map);
}
