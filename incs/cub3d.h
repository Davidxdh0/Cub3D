/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:58:45 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/03 15:27:20 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "parser.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"

# define WIDTH 1920
# define HEIGHT 1080
# define SIZE HEIGHT / 4

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
	mlx_t			*mlx;
	mlx_image_t		*win;
	mlx_image_t		*bg;
	mlx_image_t		*minimap;
	t_player		player;
	t_txtrs			txtrs;
	char			**map;
	int				width;
	int				height;
	int				sq_size;
	int				draw;
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
	double		map_x;
	double		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		height;
	int		start;
	int		end;
	int		color;
}				t_ray;

typedef enum e_wall
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}			t_wall;


void	rotate(mlx_key_data_t data, t_gen *gen);
void	movement(void *param);
void	scrolling(void *param);
void	drawMap2D(t_gen *gen);
void	draw_background(t_gen *gen);
void	cast_ray(t_gen *gen, t_player *player, int x);
void	bresenham(t_gen *gen, int x1, int y1, int x2, int y2);
void	init_gen(t_gen *gen, mlx_t *mlx, t_map *cmap);
void	render_screen(void *param);
void	init_player(t_gen *gen, mlx_t *mlx, t_map *cmap);


//keys.c
// void	walk(t_gen *gen);
void	close_escape(t_gen *gen);
void	rotate_right(t_gen *gen);
void	rotate_left(t_gen *gen);
void	walk_forwards(t_gen *gen, double move);
void	walk_backwards(t_gen *gen, double move);
void	walk_left(t_gen *gen, double move);
void	walk_right(t_gen *gen, double move);

#endif