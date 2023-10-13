/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/13 14:34:36 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	error_message(t_map *map, char *msg)
{
	if (map->error == 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
		map->error = 1;
	}
	return (EXIT_FAILURE);
}

void	error_status(t_map *map, char *msg)
{
	if (map->error == 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
		map->error = 1;
	}
}

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
