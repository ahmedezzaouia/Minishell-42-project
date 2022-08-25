/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:35:47 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/25 02:46:46 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

static	int	error_export(char *str)
{
	write(2, "Minishell : unset : `", 22);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	return (0);
}

static int	check_args_unset(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (error_export(str));
	i++;
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
			break ;
		i++;
	}

	if (str[i] == '\0')
		return (1);
	else
		return (error_export(str));
}

void	ft_unset(t_AST *cmd)
{
	int	i;

	i = 1;

	if (cmd->size_args == 1)
		return ;
	while (i < cmd->size_args)
	{
		if (check_args_unset(cmd->args[i]))
			delete_env(cmd->args[i]);
		i++;
	}
}
