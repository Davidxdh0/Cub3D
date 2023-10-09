/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   backup.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 20:57:21 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/09 23:11:07 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"
// not being used
// void	draw_vert_line(t_gen *gen, t_ray *ray, int x)
// {
// 	if (ray->side == 0)
// 		ray->walldist = ray->sidedist_x - ray->deltadist_x;
// 	else
// 		ray->walldist = ray->sidedist_y - ray->deltadist_y;
// 	ray->height = (int)(HEIGHT / ray->walldist);
// 	ray->start = -ray->height / 2 + HEIGHT / 2;
// 	ray->end = ray->height / 2 + HEIGHT / 2;
// 	if (ray->start < 0)
// 		ray->start = 0;
// 	if (ray->end >= HEIGHT)
// 		ray->end = HEIGHT - 1;
// 	if (ray->side == 1)
// 		ray->color = get_colors(gen->map[(int)ray->map_y][(int)ray->map_x]);
// 	else
// 		ray->color = get_colors(gen->map[(int)ray->map_y][(int)ray->map_x]) / 2;
// 	while (ray->start < ray->end)
// 	{
// 		mlx_put_pixel(gen->win, WIDTH - x, ray->start, ray->color);
// 		++ray->start;
// 	}
// }

// if needed for debugging
void	print_map(char **array, int ymax, int xmax)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			printf("%c", array[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	x = 0;
	printf("\nSize map: \nY = %d\nX = %d\n", ymax, xmax);
	while (x < xmax)
	{
		ft_putchar_fd('-', 1);
		x++;
	}
	printf("\n");
}
