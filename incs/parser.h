#ifndef PARSER_H
# define PARSER_H

#include "libft.h"
#include <stdio.h> // printf
#include <fcntl.h> // open
#include <stdlib.h> // exit
#include <stdbool.h> // bool

typedef struct s_txtrs
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char    *C;
	char    *F;
}	t_txtrs;

typedef struct s_map
{
	t_txtrs *txtrs;
	char 	**map;
	int		startX;
	int		startY;
	int		y_max;
	int		x_max;

}	t_map;

//error.c
void	error_message(char* msg);
void	error_exit(char* msg);

//parser.c
void	parse_line(char *line, t_map *map);
int		parse_textures(char *line, t_map *map, char *word);
int		parse_colors(char *line, t_map *c_map, char *word);
void	parse_map(char *line, t_map *c_map, int y);
int		start_position(char c);
int		open_file(char *map);
void	parser(char *map, t_map *c_map);

//parser_util.c
void	check_width_height(char *file, t_map *map);
char*	get_first_word(char* line);
int		type_value(char *word);
void	print_map(const t_map *map, char **array);
void	allocate_map(t_map *map);

//validate_map.c
void	valid_space(char **array, int x,int y);
void    validate_map(const t_map *c_map);
void    flood_fill(const t_map *c_map, char **map, int x,int y);

//free.c
void	free_t_map(t_map *map);

//init.c
t_map* 	init_map();
#endif