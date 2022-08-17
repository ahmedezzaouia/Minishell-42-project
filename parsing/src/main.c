/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:33:41 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/17 23:22:21 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	read_cmd_line(char **cmd)
{
	*cmd = readline("\033[32mMinishell$ \033[0m");
	if (*cmd == NULL)
	{
		write(2, "\033[32mMinishell$ exit\n", 22);
		exit(1);
	}
	if (cmd[0][0] == '\0')
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_pipes		*ast;
	t_parser	*parser;
	char		*cmd_line;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		if (!read_cmd_line(&cmd_line))
			continue ;
		add_history(cmd_line);
		check_error_max_here_doc(cmd_line);
		parser = init_parser(cmd_line);
		ast = parser_parse(parser);
		free_parser(parser);
		visitor(ast);
		// if(ast)
		// 	execution(ast, env);
		free_ast_pipe(ast);
		}
	return (g_exit_status);
}
