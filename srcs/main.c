/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 08:55:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/20 12:18:25 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"

int	main(int argc, char *argv[])
{
	t_map c_map;
	if (argc == 2)
	{
		parser(argv[1], &c_map);
        print_map(c_map);
        validateMap(c_map);
	}
	return (1);
}

