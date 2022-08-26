/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 04:08:51 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/26 02:12:06 by ahmez-za         ###   ########.fr       */
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

char	*expand_variable(char *str)
{
	int	i;
	int j = 0;
	char *new_str;
	char *var;
	char *temp;
	i = 0;
	new_str= ft_strdup_er("");
	while (str[i])
	{
		if(str[i] == '$' && (str[i + 1] != ' ' && str[i + 1] != '\'' && str[i + 1] != '"'))
		{
			printf("here\n");
			i++;
			j = i;
			while (str[j] && (str[j] != ' ' && str[j] != '\'' && str[j] != '"'))
				j++;
			var = ft_substr(str, i, j - i) ;
			temp = var;
			var = ft_get_env(var);
			free(temp);
			new_str = ft_strjoin(new_str, var);
			free (var);
			i = j;
		}
		if (str[i])
			new_str = ft_strjoin_char(new_str, str[i]);
		i++;
	}
	free (str);
	return (new_str);
}

void    ft_herdoc(t_pipes *ast)
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
					if (ft_strchr(str, '$'))
					{
						str = expand_variable(str);	
					}


					if (get_dollar_index(str) != -1)
					{
						str = expand_variable(str);
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
}
