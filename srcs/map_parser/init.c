/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:55:31 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/23 00:59:17 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->txtrs = malloc(sizeof(t_txtrs));
	if (!map->txtrs)
		free_t_map(map);
	map->txtrs->NO = NULL;
	map->txtrs->SO = NULL;
	map->txtrs->WE = NULL;
	map->txtrs->EA = NULL;
	map->txtrs->C = NULL;
	map->txtrs->F = NULL;
	map->map = NULL;
	map->startY = -1;
	map->startX = -1;
	map->y_max = -1;
	map->x_max = -1;
	return (map);
}
