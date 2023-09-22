/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:55:31 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 20:58:39 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->txtrs = malloc(sizeof(t_txtrs));
	map->txtrs->NO = NULL;
	map->txtrs->SO = NULL;
	map->txtrs->WE = NULL;
	map->txtrs->EA = NULL;
	map->map = NULL;
	map->startY = -1;
	map->startX = -1;
	map->y_max = -1;
	map->x_max = -1;
	return (map);
}
