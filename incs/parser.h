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
	size_t	y_max;
	size_t	x_max;

}	t_map;

//error.c
void	errorMessage(char* msg);
void	errorExit(char* msg);

//parser.c
void	parseLine(char *line, t_map *map);
void	parseTextures(char *line, t_map *c_map);
void	parseColors(char *line, t_map *c_map);
void	parseMap(char *line, t_map *c_map);

int		open_file(char *map, int fd);
void	parser(char *map, t_map *c_map);

//parser_util.c
void	init_map(t_map *map);
void	check_width_height(char *file, t_map *map);
char*	getFirstWord(char* line);
int		countTypes(char *word);
void	print_map(t_map *map);
void	fill_map(t_map *map);
void	allocate_map(t_map *map);

//validate_map.c
void    validateMap(t_map c_map);
int     floodfill(t_map c_map, size_t x, size_t y);

#endif