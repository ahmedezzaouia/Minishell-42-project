/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:54:47 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/20 15:40:02 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_position;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		next_position = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_position;
	}
}
