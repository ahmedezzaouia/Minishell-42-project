/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:05:57 by ahmaidi           #+#    #+#             */
/*   Updated: 2021/11/20 16:19:59 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*free_lst(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*position;
	t_list	*copy_by_f;
	t_list	*news;
	void	*temp;

	position = lst;
	copy_by_f = NULL;
	if (!lst)
		return (NULL);
	while (position)
	{
		temp = f(position->content);
		if (!temp)
		{
			return (free_lst(copy_by_f, del));
		}
		news = ft_lstnew(temp);
		if (!news)
		{
			return (free_lst(copy_by_f, del));
		}
		ft_lstadd_back(&copy_by_f, news);
		position = position->next;
	}
	return (copy_by_f);
}
