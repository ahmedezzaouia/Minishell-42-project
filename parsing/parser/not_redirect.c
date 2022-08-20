/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:25:00 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/20 16:49:22 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	not_redirect(t_tocken *tocken)
{
	if (tocken)
	{
		if (tocken->type == TOCKEN_GREAT
			|| tocken->type == TOCKEN_DGREAT || tocken->type == TOCKEN_LESS
			|| tocken->type == TOCKEN_HER_DOC)
			return (0);
	}
	return (1);
}
