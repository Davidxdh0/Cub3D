/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 13:32:42 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/13 18:07:38 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "graphics.h"
#include "cub3D.h"

void	scrolling(double xdelta, double ydelta, void *param)
{
	t_gen	*gen;

	(void)xdelta;
	gen = (t_gen *)param;
	if (ydelta > 0)
		rotate_left(gen);
	else if (ydelta < 0)
		rotate_right(gen);
}

void	door_key(t_gen *gen, int key)
{
	int		x;
	int		y;
	char	**map;

	x = (int)round(gen->player.x + gen->player.dir_x);
	y = (int)round(gen->player.y + gen->player.dir_y);
	map = gen->map;
	if (x == (int)gen->player.x && y == (int)gen->player.y)
		return ;
	if (x < 0 || x >= gen->width || y < 0 || y >= gen->height)
		return ;
	if (map[y][x] && map[y][x] == 'l' && key == 0)
		map[y][x] = 'c';
	else if (map[y][x] && map[y][x] == 'c' && key == 1)
		map[y][x] = 'l';
}

void	clicking(mouse_key_t but, action_t act, modifier_key_t mods, void *par)
{
	t_gen	*gen;

	(void)mods;
	gen = (t_gen *)par;
	if (but == 0 && act == 1)
	{
		door_key(gen, 1);
		gen->draw = 1;
	}
	else if (but == 1 && act == 1)
	{
		door_key(gen, 0);
		gen->draw = 1;
	}
}
