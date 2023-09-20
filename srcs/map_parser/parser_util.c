#include "parser.h"

char*	getFirstWord(char* line)
{
	char *str;

	size_t i = 0;
	size_t start = 0;
	while(line[i] && ft_isspace(line[i]))
		i++;
	if (ft_isdigit(line[i]))
	{
		// errorExit("Weird bug, countmap()");
		return (NULL);
	}
	if (line[i] && ft_isalpha(line[i]))
	{
		start = i;
		while (line[i] && ft_isalpha(line[i]))
			i++;
		str = malloc(sizeof(char *) * i - start + 1);
		if (!str)
			return (NULL);
		// printf("i=%zu, start=%zu, str=%s, line=%s", i, start, str, line);
		ft_strlcpy(str, line, i - start + 1);
		// printf("i=%zu, start=%zu, str=%s, line=%s", i, start, str, line);
	}
	else
		str = NULL;
	return (str);
}

//colors	= F:2, C:3
//textures 	= NO:11, SO:12, WE:14, EA:20
//combined 	= 57; no other possibilty to get 57.
int	countTypes(char *word)
{
	int type;

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
		errorExit("Weird bug, countmap()");
	return (type);
}

void	check_width_height(char *file, t_map *map)
{
	int fd;
	char *line;
	size_t	i;
	size_t	start;

	start = 0;
	fd = open_file(file, 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while(line[i] && ft_isspace(line[i]))
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
		line = get_next_line(fd);
	}
	map->y_max -= start;
	close(fd);
}

void	allocate_map(t_map *map)
{
	size_t i;

	i = 0;
	map->map = (char**)malloc(sizeof(char *) * map->y_max);
	if (!map->map)
		errorExit("Malloc map->map");
	while (i < map->y_max)
	{
		map->map[i] = (char *)malloc(sizeof(char) * (map->x_max + 1));
		if (!map->map[i])
			errorExit("Malloc map->map[y]");
		i++;
	}
}

void	fill_map(t_map *map)
{
	size_t y;
	size_t x;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			map->map[y][x] = 'X';
			x++;
		}
		y++;
	}
}

void	print_map(t_map *map)
{
	size_t y;
	size_t x;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			printf("-%c-", map->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	init_map(t_map *map)
{
    map->txtrs      = malloc(sizeof (t_txtrs));
    map->txtrs->NO  = NULL;
    map->txtrs->SO  = NULL;
    map->txtrs->WE  = NULL;
    map->txtrs->EA  = NULL;
	map->map	    = NULL;
	map->y_max	    = 0;
	map->x_max	    = 0;
}
