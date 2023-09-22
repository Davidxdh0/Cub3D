/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:17 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 20:47:45 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_t_map(t_map *map)
{
	free(map->txtrs);
	ft_free_arr(map->map);
	free(map);
}
