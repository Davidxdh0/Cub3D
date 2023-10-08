/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:58:45 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/08 12:40:14 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "parser.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

# define WIDTH 1920
# define HEIGHT 1080
# define SIZE HEIGHT/4

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		dir;
	mlx_image_t	*img;
}				t_player;

typedef struct s_gen
{
	mlx_t		*mlx;
	mlx_image_t	*win;
	mlx_image_t	*bg;
	mlx_image_t	*minimap;
	t_player	player;
	t_txtrs		txtrs;
	char		**map;
	int			width;
	int			height;
	int			sq_size;
	int			draw;
}				t_gen;

typedef struct s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	walldist;
	double	map_x;
	double	map_y;
	double	wall_x;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		height;
	int		start;
	int		end;
	int		color;
}			t_ray;

void	scrolling(void *param);

void	init_gen(t_gen *gen, mlx_t *mlx, t_map *cmap);

//free
void	free_textures(t_gen *gen);

#endif