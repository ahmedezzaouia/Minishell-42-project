/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:33:41 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/23 03:43:48 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/parsing.h"

int	read_cmd_line(char **cmd)
{
	*cmd = readline("\033[32mMinishell$ \033[0m");
	if (*cmd == NULL)
	{
		write(1, "\033[91mMinishell$ Exit\033[0m\n", 26);
		exit(EXIT_SUCCESS);
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
	env_variable(&(g_data.env_list), env);
	while (1)
	{
		if (!read_cmd_line(&cmd_line))
			continue ;
		add_history(cmd_line);
		check_error_max_here_doc(cmd_line);
		parser = init_parser(cmd_line);
		ast = parser_parse(parser);
		free_parser(parser);
		//visitor(ast);
		if (ast)
		{
			char *str;
			int	i;
			int j;

			i = 0;
			j = 0;
			str = NULL;
			while (i < ast->nbre_pipes)
			{
				j = 0;
				while (j < ast->tab_cmd[i]->size_redirec)
				{
					if (ast->tab_cmd[i]->redirec[j]->type == HERE_DOC)
					{
						if (pipe(ast->tab_cmd[i]->redirec[j]->heredoc) == -1)
						{
							printf("Error: \n");
    						exit(1);
						}
						while ((str = readline("> ")))
						{
							if (!str)
								break ;

							if (!ft_strncmp(str, ast->tab_cmd[i]->redirec[j]->filename, ft_strlen(ast->tab_cmd[i]->redirec[j]->filename)))
						    {
						        free(str);
						        break ;
						    }
							char *sh = ft_strjoin(str, "\n");
						    ft_putstr_fd(sh, ast->tab_cmd[i]->redirec[j]->heredoc[1]);
							free(sh);
						}
						close(ast->tab_cmd[i]->redirec[j]->heredoc[1]);
						// only p[0] too get input from 
					}
					j++;
				}
				i++;
			}
			execution(ast, env);
			// ast->nbre_pipes++;
			free_ast_pipe(ast);
			system("leaks minishell");
		}
	}
	return (g_data.exit_status);

}