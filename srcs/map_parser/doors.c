/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doors.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:55:47 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/10/09 21:18:27 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	valid_chars(char c)
{
	if (c == '0')
		return (1);
	else if (c == '1')
		return (1);
	else if (c == ' ')
		return (1);
	else if (c == 'L')
		return (1);
	else if (c == 'C')
		return (1);
	else
		return (0);
}

int	is_door(char c)
{
	if (c == 'L')
		return (1);
	else if (c == 'C')
		return (1);
	return (0);
}

int	is_walkable(char c)
{
	if (c == '0')
		return (1);
	if (c == 'L')
		return (1);
	if (c == 'l')
		return (1);
	return (0);
}

int	is_changed(char c)
{
	if (c == '.')
		return (1);
	if (c == 'c')
		return (1);
	if (c == 'l')
		return (1);
	return (0);
}

void	door_key(char **array, int key)
{
	int			x;
	int			y;

	y = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (array[y][x] == 'l' && key == 1)
				array[y][x] = 'c';
			if (array[y][x] == 'c' && key == 0)
				array[y][x] = 'l';
			x++;
		}
		y++;
	}
}
