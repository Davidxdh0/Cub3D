/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   TEST.C                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 08:52:56 by bfranco       #+#    #+#                 */
/*   Updated: 2023/09/24 16:44:44 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

#define SIZE 64
#define mapX 24
#define mapY 24
#define WIDTH 800
#define HEIGHT 600

int map[mapX][mapY] = \
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_square(mlx_t *mlx, int x, int y, int color)
{
	int			i;
	int			j;
	mlx_img_t	*img;

	i = 0;
	img = mlx_new_image(mlx, SIZE / 4, SIZE / 4);
	memset(img->pixels, color, img->width * img->height * sizeof(int32_t));
	mlx_imaget_to_window(mlx, img, x * SIZE, y * SIZE);
	mlx_delete_image(mlx, img);
}

void drawMap2D(t_gen *gen)
{
	int			x;
	int			y;
	int			color;

	y = -1;
	while (++y < mapY)
	{
		x = -1;
		while (++x < mapX)
		{
			if (map[y][x] > 0)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(gen->mlx, x, y, color);
		} 
	} 
}


// void	draw_ray(t_gen *gen)
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < 1)
	
// }

void	init_gen(t_gen *gen, mlx_t *mlx)
{
	gen->mlx = mlx;
	gen->player.pos.x = 2;
	gen->player.pos.y = 2;
	gen->player.dir.x = -1;
	gen->player.dir.y = 0;
	gen->player.plane.x = 0;
	gen->player.plane.y = 0.66;
	gen->win = mlx_new_image(mlx, WIDTH, HEIGHT);
}

int	main(void)
{
	mlx_t	*mlx;
	t_gen	gen;

	mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!mlx)
		return (EXIT_FAILURE);
	init_gen(&gen, mlx);
	clear_screen(&gen, 0x00000000);
	// mlx_loop_hook(mlx, render_screen, &gen);
	// mlx_key_hook(mlx, ft_hook, &gen);
	drawMap2D(&gen)
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}