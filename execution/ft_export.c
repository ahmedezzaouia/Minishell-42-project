/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:49:29 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/08/29 00:13:14 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

static int	error_export(char *str)
{
	write(2, "Minishell : export : `", 23);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	g_data.exit_status = 1;
	return (0);
}

static int	check_args_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (error_export(str));
	i++;
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_')
			|| str[i] == '=' || str[i] == '+')
			break ;
		i++;
	}
	if (str[i] == '+' && str[i + 1] == '=')
		return (1);
	if (str[i] == '=' || str[i] == '\0')
		return (1);
	else
		return (error_export(str));
}

int	ft_index_env(char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	len = i;
	if (str[i] != '\0' && str[i - 1] == '+')
		len--;
	i = 0;
	while (g_data.env_list[i])
	{
		if (!ft_strncmp(g_data.env_list[i], str, len))
			return (i);
		i++;
	}
	return (0);
}

void	ft_export(t_AST *cmd)
{
	int	i;

	i = 1;
	i += !ft_strncmp(cmd->args[i], "--", ft_strlen(cmd->args[i]));
	if (display_export(cmd))
	{
		while (i < cmd->size_args)
		{
			if (check_args_export(cmd->args[i]))
			{
				if (ft_index_env(cmd->args[i]))
					update_env(cmd->args[i]);
				else
					ft_export_add(cmd, i);
				g_data.exit_status = 0;
			}
			i++;
		}
	}
}
