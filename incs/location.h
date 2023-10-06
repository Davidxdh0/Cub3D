/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/24 01:04:06 by daaf          #+#    #+#                 */
/*   Updated: 2023/10/06 10:28:51 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_H
# define LOCATION_H
# define WIDTH 512
# define HEIGHT 512

# include <stdio.h>

typedef struct s_gps
{
	int	x;
	int	y;
	int	z;
}	t_gps;

#endif
