/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:10:00 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/20 17:11:20 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *news)
{
	if (lst == NULL || news == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = news;
	}
	else
	{
		news->next = *lst;
		*lst = news;
	}	
}
