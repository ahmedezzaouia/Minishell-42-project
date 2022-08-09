/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:33:41 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/09 15:21:26 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	main(void)
{
	t_lexer		*lexer;
	t_tocken	*t;
	char		*line;
	int			fd;

	fd = open("parsing/src/file.txt", O_RDONLY, 0644);
	if (fd == -1)
		ft_error(errno);
	line = get_next_line(fd);
	lexer = init_lexer(line, 0);
	t = (void *)0;
	while ((t = lexer_get_next_tocken(lexer))->type != 6)
	{
		printf("1 TOCKEN(%d ||%s)\n", t->type, t->value);
		free(t->value);
		free(t);
	}
	printf("1 TOCKEN(%d ||%s)\n", t->type, t->value);
		free(t->value);
		free(t);
	// while (1)
	// 	;
	return (0);
}
