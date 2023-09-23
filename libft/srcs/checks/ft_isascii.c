/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:11:34 by bfranco       #+#    #+#                 */
/*   Updated: 2022/10/17 08:19:23 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int n)
{
	return (n >= 0 && n <= 127);
}