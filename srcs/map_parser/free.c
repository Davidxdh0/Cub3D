/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:17 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/25 15:29:24 by daaf          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_arr(char **arg, int max)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (i < max && arg[i])
		free(arg[i++]);
	free(arg);
}

// 	ft_free_arr(map->map); gives invalid read
void	free_t_map(t_map *map)
{
	free(map->txtrs);
	if (map->map != NULL)
		free_arr(map->map, map->y_max);
	free(map);
}
