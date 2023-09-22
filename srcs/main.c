/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 08:55:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 22:32:51 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"

int	main(int argc, char *argv[])
{
	t_map	*c_map;

	c_map = NULL;
	if (argc == 2)
	{
		c_map = init_map();
		parser(argv[1], c_map);
		validate_map(c_map);
		print_map(c_map, c_map->map);
	}
	free_t_map(c_map);
	return (1);
}
