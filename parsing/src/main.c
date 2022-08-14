/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:33:41 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/14 23:13:20 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

static int	check_here_max_doc(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i] == '<')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

static int	exit_error_max_here_doc(int g_exit_status)
{
	write(2, "maximum here-document count exceeded\n", 38);
	g_exit_status = 258;
	return (g_exit_status);
}

int	main(void)
{
	t_AST		*ast;
	t_parser	*parser;
	char		*line;
	int			fd;

	fd = open("parsing/src/file.txt", O_RDONLY, 0644);
	if (fd == -1)
		ft_error(errno);
	line = get_next_line(fd);
	if (check_here_max_doc(line) >= 17)
		return (exit_error_max_here_doc(g_exit_status));
	parser = init_parser(line, g_exit_status);
	ast = parser_parse(parser);
	visitor_vis(ast);
	free_ast_pipe(ast);
	return (g_exit_status);
}
