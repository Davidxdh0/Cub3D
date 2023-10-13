/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:22:16 by bfranco       #+#    #+#                 */
/*   Updated: 2023/10/13 14:32:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
