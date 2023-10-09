/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 10:44:15 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/09 17:23:48 by dyeboa        ########   odam.nl         */
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
	mlx_texture_t	*t_text;
	mlx_texture_t	*t_one;
	mlx_texture_t	*t_two;

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
	int		error;
	char	dir;
}	t_map;

//error.c
int		error_message(t_map *map, char *msg);
void	error_status(t_map *map, char *msg);
void	error_exit(char *msg);
void	error_free(char *msg, t_map *map);

//parser
int		parse_line(char *line, t_map *map);
int		parser(char *map, t_map *c_map);
int		parse_textures(char *line, t_map *map, char *word);
int		parse_colors(char *line, t_map *c_map, char *word);
int		parse_map(char *line, t_map *c_map, int y);
int		type_value(char *word);
char	start_position(char c);
void	check_width_height(t_map *map, int start, int fd);
char	*get_first_word(char *line);
void	print_map(char **array, int ymax, int xmax);
char	**allocate_map(char **map, int y, int x);
int		get_colors(t_map *map, char **words, char **colors);

int		parse_file(t_map *c_map, char *file);
int		check_texture_files(t_map *map, char *words, char *ext);
int		check_extension(t_map *map, char *file, char *ext);
int		open_file(t_map *map, char *file);

//validate_map.c
void	valid_space(t_map *c_map, char **arr, int x, int y);
int		validate_map(t_map *c_map);
void	flood_fill(t_map *c_map, char **map, int x, int y);
void	fill_map(t_map *c_map, char **old_map, int ymax, int xmax);

//new_map_vaiables.c
void	width_validated_map(t_map *c_map, int y, int x);
void	heigth_validated_map(t_map *c_map);
void	find_new_start_pos(t_map *map);

//free.c
int		destroy_map(t_map *map);
void	free_t_map(t_map *map);
//void	free_textures(t_gen *gen);

//init.c
t_map	*init_map(void);

#endif
