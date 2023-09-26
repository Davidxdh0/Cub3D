/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:58:45 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/26 22:19:43 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"


# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SIZE 64
# define WIDTH 1920
# define HEIGHT 1080
# define SPEED 0.5
# define ROTATE 0.5

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	double		x;
	double		y;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	mlx_image_t	*img;
}				t_player;

typedef struct s_gen
{
	mlx_t			*mlx;
	mlx_image_t		*win;
	int				**map;
	t_player		player;
}				t_gen;

typedef struct s_ray
{
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;
}				t_ray;

typedef enum e_wall
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}			t_wall;

void	walk(mlx_key_data_t data, t_gen *gen);
void	rotate(mlx_key_data_t data, t_gen *gen);
void	movement(mlx_key_data_t data, void *param);
void	drawMap2D(t_gen *gen);
void	cast_ray(t_gen *gen, t_player *player, int x);
void	bresenham(t_gen *gen, int x1, int y1, int x2, int y2);


#endif
