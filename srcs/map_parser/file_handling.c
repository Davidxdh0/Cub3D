/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 20:37:45 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/06 19:54:43 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_extension(char *file)
{
	int		len;
	char	*extension;

	len = ft_strlen(file);
	if (len < 5)
		error_exit("Invalid file name");
	extension = ft_strrchr(file, '.');
	if (!extension)
		error_exit("Extension not found");
	if (strncmp(extension, ".cub", 5))
		error_exit("Invalid file extension");
}

int	open_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");
	return (fd);
}
