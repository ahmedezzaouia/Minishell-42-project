/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:32:48 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/20 16:19:09 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *news)
{
	t_list	*last;

	if (lst == NULL || news == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = news;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = news;
	}
}
