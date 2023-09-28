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
	int		y_start;
	int		x_start;
	int		y_max;
	int		x_max;

}	t_map;

//error.c
void	error_message(char* msg);
void	error_exit(char* msg);
void	error_free(char *msg, t_map *map);

//parser
void	parse_line(char *line, t_map *map);
int		open_file(char *map);
void	parser(char *map, t_map *c_map);
int		parse_textures(char *line, t_map *map, char *word);
int		parse_colors(char *line, t_map *c_map, char *word);
int		parse_map(char *line, t_map *c_map, int y);
int		type_value(char *word);
int		start_position(char c);
void	check_width_height(t_map *map, int start, int fd);
char*	get_first_word(char* line);
void	print_map(const t_map *map, char **array);
char**	allocate_map(char **map, int y, int x);
int		count_array(char **array);
void	check_extension(char *file);

//validate_map.c
void	valid_space(char **array, int x,int y);
void    validate_map(t_map *c_map);
void    flood_fill(t_map *c_map, char **map, int x,int y);
int		heigth_validated_map(t_map *c_map);
int		width_validated_map(t_map *c_map);
void	fill_map(t_map *c_map, char **old_map, int ymax, int xmax);
//free.c
void	free_t_map(t_map *map);
void	free_arr(char **arg, int max);


//init.c
t_map* 	init_map();

#endif