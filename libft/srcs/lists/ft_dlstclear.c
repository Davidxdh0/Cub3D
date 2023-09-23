/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlstclear.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 12:21:22 by bfranco       #+#    #+#                 */
/*   Updated: 2023/01/03 16:07:49 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

void	ft_dlstclear(t_dlist **lst)
{
	t_dlist	*ptr;
	t_dlist	*ptr2;

	ptr = *lst;
	while (ptr)
	{
		ptr2 = ptr->next;
		ft_dlstdelone(ptr);
		ptr = ptr2;
	}
	*lst = NULL;
	free(lst);
}
