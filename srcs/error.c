/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 13:56:43 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	error_message(t_map *map, char *msg)
{
	if (map->error == 0)
	{
		printf("Error\n");
		printf("%s\n", msg);
		map->error = 1;
	}
	return (EXIT_FAILURE);
}

void	error_status(t_map *map, char *msg)
{
	if (map->error == 0)
	{
		printf("Error\n");
		printf("%s\n", msg);
		map->error = 1;
	}
}

void	error_exit(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(1);
}
