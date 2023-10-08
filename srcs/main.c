/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 08:55:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/08 21:17:29 by daaf          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "graphics.h"
#include "player.h"
#include "cub3d.h"

//valgrind --leak-check=full --show-leak-kinds=all 
// --track-origins=yes ./cub3D maps/default.cub
int	main(int argc, char *argv[])
{
	mlx_t	*mlx;
	t_gen	gen;
	t_map	*c_map;

	c_map = NULL;
	if (argc == 2)
	{
		c_map = init_map();
		parser(argv[1], c_map);
		validate_map(c_map);
		mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
		if (!mlx)
			return (EXIT_FAILURE);
		init_gen(&gen, mlx, c_map);
		draw_background(&gen);
		draw_minimap(&gen);
		mlx_loop_hook(mlx, movement, &gen);
		// mlx_scroll_hook(mlx, scrolling, &gen);
		mlx_loop(mlx);
		free_textures(&gen);
		ft_free_arr(gen.map);
		mlx_terminate(mlx);
	}
	return (EXIT_SUCCESS);
}

void	render_screen(void *param)
{
	t_gen		*gen;
	int			x;
	t_vector	pos;

	gen = (t_gen *)param;
	x = 0;
	mlx_delete_image(gen->mlx, gen->win);
	gen->win = mlx_new_image(gen->mlx, WIDTH, HEIGHT);
	draw_minimap(gen);
	memset(gen->win->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	while (x < WIDTH)
	{
		cast_ray(gen, &gen->player, x);
		++x;
	}
	pos.x = gen->player.x * gen->sq_size;
	pos.y = gen->player.y * gen->sq_size;
	mlx_image_to_window(gen->mlx, gen->win, 0, 0);
	mlx_set_instance_depth(&gen->win->instances[0], 1);
	mlx_image_to_window(gen->mlx, gen->minimap, 0, 0);
	mlx_set_instance_depth(&gen->minimap->instances[0], 2);
	mlx_image_to_window(gen->mlx, gen->player.img, pos.x, pos.y);
	mlx_set_instance_depth(&gen->player.img->instances[0], 5);
	gen->draw = 0;
}
