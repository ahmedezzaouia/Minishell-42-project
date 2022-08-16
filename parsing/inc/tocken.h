/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:58:53 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/16 00:36:28 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOCKEN_H
# define TOCKEN_H
# include <stdio.h>
# include <stdlib.h>

typedef enum s_tocken_type
{
	TOCKEN_WORD,
	TOCKEN_PIPE,
	TOCKEN_GREAT,
	TOCKEN_DGREAT,
	TOCKEN_LESS,
	TOCKEN_HER_DOC,
	TOCKEN_EOF
}	t_tocken_type;

typedef struct s_tocken
{
	t_tocken_type	type;
	char			*value;
}	t_tocken;

t_tocken	*init_tocken(t_tocken_type	type, char *value);
#endif