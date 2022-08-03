/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:08:23 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/07/31 19:22:38 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

t_tocken	*init_tocken(t_tocken_type	type, char *value)
{
	t_tocken	*tocken;

	tocken = ft_calloc(1, sizeof(t_tocken));
	tocken->type = type;
	tocken->value = value;
	return (tocken);
}
