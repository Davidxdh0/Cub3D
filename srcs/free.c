/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:17 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 13:02:04 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"

int	kill_program(t_map *map)
{
	if (map->map)
		ft_free_arr(map->map);
	if (map->txtrs.no)
		free(map->txtrs.no);
	if (map->txtrs.so)
		free(map->txtrs.so);
	if (map->txtrs.we)
		free(map->txtrs.we);
	if (map->txtrs.ea)
		free(map->txtrs.ea);
	free(map);
	return (EXIT_FAILURE);
}

void	free_t_map(t_map *map)
{
	if (map->map != NULL)
		ft_free_arr(map->map);
	free(map);
}

void	free_textures(t_gen *gen)
{
	free(gen->txtrs.no);
	free(gen->txtrs.so);
	free(gen->txtrs.we);
	free(gen->txtrs.ea);
	mlx_delete_texture(gen->txtrs.t_no);
	mlx_delete_texture(gen->txtrs.t_so);
	mlx_delete_texture(gen->txtrs.t_we);
	mlx_delete_texture(gen->txtrs.t_ea);
}
