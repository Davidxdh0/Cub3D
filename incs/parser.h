/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 10:44:15 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/07 20:16:35 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

typedef struct s_txtrs
{
	mlx_texture_t	*t_no;
	mlx_texture_t	*t_so;
	mlx_texture_t	*t_we;
	mlx_texture_t	*t_ea;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int32_t			ceil;
	int32_t			floor;
}	t_txtrs;

typedef struct s_map
{
	t_txtrs	txtrs;
	char	**map;
	int		start_x;
	int		start_y;
	int		y_start;
	int		x_start;
	int		y_max;
	int		x_max;
	char	dir;
}	t_map;

//error.c
void	error_message(char *msg);
void	error_exit(char *msg);
void	error_free(char *msg, t_map *map);

//parser
void	parse_line(char *line, t_map *map);
int		open_file(char *map);
void	parser(char *map, t_map *c_map);
int		parse_textures(char *line, t_map *map, char *word);
int		parse_colors(char *line, t_map *c_map, char *word);
int		parse_map(char *line, t_map *c_map, int y);
int		type_value(char *word);
char	start_position(char c);
void	check_width_height(t_map *map, int start, int fd);
char	*get_first_word(char *line);
void	print_map(char **array, int ymax, int xmax);
char	**allocate_map(char **map, int y, int x);
void	get_colors(t_map *map, char **words, char **colors);
void	check_extension(char *file);

//validate_map.c
void	valid_space(char **array, int x, int y);
void	validate_map(t_map *c_map);
void	flood_fill(t_map *c_map, char **map, int x, int y);
void	heigth_validated_map(t_map *c_map);
void	width_validated_map(t_map *c_map);
void	fill_map(t_map *c_map, char **old_map, int ymax, int xmax);
void	find_new_start_pos(t_map *map);

//free.c
void	free_t_map(t_map *map);

//init.c
t_map	*init_map(void);

#endif
