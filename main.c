/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:33:41 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/27 05:47:17 by ahmez-za         ###   ########.fr       */
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

void sig_handler(int sig)
{
	
	if (sig == SIGINT)
	{
		if (g_data.is_herdoc == 1)
		{
			g_data.is_herdoc = 0;
			g_data.kill_herdoc = 1;
			close(0);
		}
		else
		{
			if (g_data.is_child == 1)
			{
				printf("enterr .....\n");
				g_data.is_child = 0;
				printf("\n");
				rl_on_new_line();
				rl_replace_line("", 0);
			}
			else
			{				
				printf("\n");
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}

		}
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	
	if (sig == SIGQUIT)
	{
		if(g_data.is_child == 1)
		{
			printf("^\\Quit: 3\n");
		}
	}
}

void	close_herdoc_pipes(t_pipes *cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmds->nbre_pipes)
	{
		j = 0;
		while (j < cmds->tab_cmd[i]->size_redirec)
		{
			if (cmds->tab_cmd[i]->redirec[j]->heredoc[0])
				close(cmds->tab_cmd[i]->redirec[j]->heredoc[0]);
			j++;
		}
		i++;
	}
	
}

int	main(int ac, char **av, char **env)
{
	t_pipes		*ast;
	t_parser	*parser;
	char		*cmd_line;
	int			input;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	input = dup(0);
	signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
	env_variable(env);
	while (1)
	{
		g_data.num_of_cmds = 1;
		g_data.is_herdoc = 0;
		g_data.kill_herdoc = 0;
		g_data.is_child = 0;
		
		if (!read_cmd_line(&cmd_line))
			continue ;
		add_history(cmd_line);
		check_error_max_here_doc(cmd_line);
		parser = init_parser(cmd_line);
		ast = parser_parse(parser);
		free_parser(parser);
		// visitor(ast);
		if (ast)
		{
			g_data.num_of_cmds = ast->nbre_pipes;
			ft_herdoc(ast);
			if (g_data.kill_herdoc == 0)
				execution(ast, g_data.env_list);
			close_herdoc_pipes(ast);
			free_ast_pipe(ast);
			dup2(input, 0);
		}
		//system("leaks minishell");
	}
	return (g_data.exit_status);
}
