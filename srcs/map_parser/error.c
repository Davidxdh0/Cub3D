/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 20:44:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/09/22 21:01:32 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	error_message(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
}

void	error_exit(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(0);
}
