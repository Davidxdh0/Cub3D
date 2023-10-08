/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 20:37:45 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/08 18:15:36 by daaf          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_extension(char *file, char *ext)
{
	int		len;
	int		len_ext;
	char	*extension;

	len = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (len < 5)
		error_exit("Invalid file name");
	extension = ft_strrchr(file, '.');
	if (!extension)
		error_exit("Extension not found");
	if (strncmp(extension, ext, len_ext))
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
