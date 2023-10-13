/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 20:37:45 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/13 18:14:22 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_file(t_map *c_map, char *file)
{
	int	fd;

	if (check_extension(c_map, file, ".cub") == 1)
		return (EXIT_FAILURE);
	fd = open_file(c_map, file);
	if (fd < 0)
		return (error_message(c_map, "Failed to open file"));
	check_width_height(c_map, 0, fd);
	close(fd);
	if (c_map->y_max == -1 || c_map->x_max == -1)
		return (error_message(c_map, "Invalid ymax or xmax"));
	return (EXIT_SUCCESS);
}

int	check_texture_files(t_map *map, char *file, char *ext)
{
	int	fd;

	fd = open_file(map, file);
	if (fd < 0)
		return (EXIT_FAILURE);
	close(fd);
	return (check_extension(map, file, ext));
}

int	check_extension(t_map *map, char *file, char *ext)
{
	int		len;
	int		len_ext;
	char	*extension;

	len = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (len < 5)
		return (error_message(map, "Invalid file name"));
	extension = ft_strrchr(file, '.');
	if (!extension)
		return (error_message(map, "Extension not found"));
	if (strncmp(extension, ext, len_ext + 1))
		return (error_message(map, "Invalid file extension"));
	return (EXIT_SUCCESS);
}

int	open_file(t_map *map, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message(map, "Failed to open file");
	return (fd);
}
