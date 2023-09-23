/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:19:53 by bfranco       #+#    #+#                 */
/*   Updated: 2022/10/17 08:19:40 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int n)
{
	return (n >= 32 && n < 127);
}