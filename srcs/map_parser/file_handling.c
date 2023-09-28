/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 20:37:45 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/28 20:45:18 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
//	printf("exten: %s\n", extension);
void	check_extension(char *file)
{
	int len;
	char *extension;

	len = ft_strlen(file);
	if (len < 5)
		error_exit("Extension not .cub");
	extension = ft_substr(file, len - 4, 4);
	if (strncmp(extension, ".cub", 4))
		error_exit("Extension not .cub");
}


int	open_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_exit("File can't be opened");
	return (fd);
}