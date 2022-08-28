/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 04:08:51 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/28 19:54:30 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

int	get_dollar_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	
	if ((int)ft_strlen(str) == i)
		return (-1);
	else
		return (i);

}

int	expand_variable_set_var(char *str, int i, char **new_str)
{
	int j;
	char *var;
	char *temp;
	
	i++;
	j = i;
	while (str[j] && (str[j] != ' ' && str[j] != '\'' && str[j] != '"'))
		j++;
	var = ft_substr(str, i, j - i) ;
	temp = var;
	var = ft_get_env(var);
	free(temp);
	*new_str = ft_strjoin(*new_str, var);
	free (var);
	i = j;
	return (i);
}

char	*expand_variable(char *str)
{
	int	i;
	char *new_str;

	i = 0;
	new_str = ft_strdup_er("");
	while (str[i])
	{
		if(str[i] == '$' && (str[i + 1] != ' ' \
			&& str[i + 1] != '\'' && str[i + 1] != '"'))
			i = expand_variable_set_var(str, i, &new_str);
		if (str[i])
			new_str = ft_strjoin_char(new_str, str[i]);
		i++;
	}
	free (str);
	return (new_str);
}

void	pipe_err()
{
	ft_putstr_fd("Pipe creation Error: \n", 2);
    exit(1);
}

void	run_herdoc(t_pipes *ast, int i, int j)
{
	char *str;

	if (ast->tab_cmd[i]->redirec[j]->type == HERE_DOC)
	{
		if (pipe(ast->tab_cmd[i]->redirec[j]->heredoc) == -1)
			pipe_err();
		while ((str = readline("> ")) && g_data.is_herdoc)
		{		
			if (!str)
				break ;
			if (!ft_strncmp(str, ast->tab_cmd[i]->redirec[j]->filename, \
				ft_strlen(ast->tab_cmd[i]->redirec[j]->filename)))
			{
				free(str);
				break ;
			}
			if (ft_strchr(str, '$'))
				str = expand_variable(str);	
			str = ft_strjoin(str, "\n");
			ft_putstr_fd(str, ast->tab_cmd[i]->redirec[j]->heredoc[1]);
			free(str);
		}
		close(ast->tab_cmd[i]->redirec[j]->heredoc[1]);
	}
}
void    ft_herdoc(t_pipes *ast)
{
	int	i;
	int j;

	i = 0;
	g_data.is_herdoc = 1;
	while (i < ast->nbre_pipes && g_data.is_herdoc)
	{
		j = 0;
		while (j < ast->tab_cmd[i]->size_redirec && g_data.is_herdoc)
		{
			run_herdoc(ast, i, j);
			j++;
		}
		i++;
	}
	g_data.is_herdoc = 0;
}
