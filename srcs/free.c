/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:17 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/06 19:40:15 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"

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
