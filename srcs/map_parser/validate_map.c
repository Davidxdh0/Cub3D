/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 09:33:04 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/20 09:33:10 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int     floodfill(t_map c_map, size_t x, size_t y)
{

    return 1;
    c_map.y_max = x + y;
}

void    validateMap(t_map c_map)
{
    int p = floodfill(c_map, 1, 1);
    p++;
    return ;
    c_map.y_max = 1;
}