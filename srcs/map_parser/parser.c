#include "parser.h"

void	parseTextures(char *line, t_map *map)
{
    printf("parseTextures");
    int i = 0;
    char **words = ft_split(line, ' ');
    if (words == NULL || !words[0]){
        errorExit("parseTextures went wrong");
    }
    while (words[i])
    {
//        printf("words[i] = %s\n", words[i]);
        i++;
    }
    if (i != 2)
        errorExit("parseTextures went wrong");
    words[1][ft_strlen(words[1])-1] = '\0';
    i = open_file(words[1], 0);
    close(i);
    printf("parseTextures \n");
    if (!strcmp(words[0], "NO") && map->txtrs->NO == NULL)
    	map->txtrs->NO = words[1];
    else if (!strcmp(words[0], "SO") && map->txtrs->SO == NULL)
       	map->txtrs->SO = words[1];
    else if (!strcmp(words[0], "WE") && map->txtrs->WE == NULL)
      	map->txtrs->WE = words[1];
    else if (!strcmp(words[0], "EA") && map->txtrs->EA == NULL)
     	map->txtrs->EA = words[1];
    else
        errorExit("parseTextures went wrong");
    ft_free_arr(words);
}

void	parseColors(char *line, t_map *c_map)
{
    printf("parseColors");
    line[ft_strlen(line)-1] = '\0';
    printf("parseColors");
    int i = 0;
    int j = 0;
    int number = 0;
    char **colors;
    char **words = ft_split(line, ' ');
    if (words == NULL || !words[0]){
        errorExit("parseTextures went wrong");
    }

    while (words[i])
    {
        printf("words[i] = %s\n", words[i]);
        i++;
    }
    if (i != 2)
        errorExit("parseColours not two words");
    colors = ft_split(words[1], ',');
    while (colors[j])
    {
        printf("colors[j] = %s\n", colors[j]);
        j++;
    }
    if (i != 2)
        errorExit("parseColors values not three words");
    i = 0;
    while (i < j){
        number = ft_atoi(colors[i]);
        printf("number = %d, i = %d\n", number, i);
        if (number < 0 || number > 255)
            errorExit("parseColors value < 0 || > 255");
        i++;
    }
    if (!strcmp(words[0], "F"))
        c_map->txtrs->F = words[1];
    else if (!strcmp(words[0], "C"))
        c_map->txtrs->C = words[1];
}

// 1 " " n s w e
void	parseMap(char *line, t_map *c_map)
{
    line[ft_strlen(line)-1] = '\0';
    printf("parseMap\n");
    static int y;
    y = 0;
    size_t i = 0;
    while (line[i] && (line[i] == '1' || line[i] == '0' || line[i] == ' ' || \
        line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'D'))
    {
        c_map->map[y][i] = line[i];
        i++;
    }
    y++;
    if (line[i]) {
        printf("i = %zu line = %s, char = %c\n", i, line, line[i]);
        errorExit("Map contains different values");
    }

}

int open_file(char *map, int fd)
{
    printf("file = %s\n", map);
	fd = open(map,  O_RDONLY);
	if (fd < 0)
		errorExit("File can't be opened");
	return (fd);
}

void	parseLine(char *line, t_map *map)
{
	char *word;
    static bool map_bool    = 0;
    static int colors       = 0; //f 2 , c 3
    static int textures     = 0; // no 11, so 12, we 14, ea 20

	if (line == NULL)
		errorExit("Empty file");
	if (line[0] == '\n')
		return ;
	word = getFirstWord(line);
//    printf("word = %s, mapbool = %d\n", word, map_bool);
	if ( word && (!strcmp(word, "F") || !strcmp(word, "C")) && map_bool == 0)
	{
        printf("parseColors");
		parseColors(line, map);
		colors += countTypes(word);
	}
	else if (word && (!strcmp(word, "NO") || !strcmp(word, "SO") || \
			 		  !strcmp(word, "WE") || !strcmp(word, "EA")) \
			&& map_bool == 0)
	{
		parseTextures(line, map);
		textures += countTypes(word);
	}
	else if (colors == 5 && textures == 57)
	{
		// printf("map!\n");
		parseMap(line, map);
		map_bool = 1;
	}
	else
		errorExit("Incorrect Textures or Colors");
//	 printf("C %d F %d\n", colors, textures);
}

void	parser(char *file, t_map *c_map)
{
	int fd;
	char *line;

	init_map(c_map);
	check_width_height(file, c_map);
	allocate_map(c_map);
	fill_map(c_map);
//    print_map(c_map);
	fd = open_file(file, 0);
	line = get_next_line(fd);
	printf("line1: %s\n", line);
	while(line && line != NULL)
	{
        parseLine(line, c_map);
		line = get_next_line(fd);
	}
	close(fd);
}