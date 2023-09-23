/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 16:48:02 by bfranco       #+#    #+#                 */
/*   Updated: 2023/01/02 18:25:01 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int n)
{
	if (n >= 'a' && n <= 'z')
		n -= 32;
	return (n);
}