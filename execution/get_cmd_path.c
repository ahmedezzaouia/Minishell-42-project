/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:52:49 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/29 13:25:05 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"

void	get_path_free(char **path_chunks)
{
	int	i;

	i = -1;
	while (path_chunks[++i])
		free(path_chunks[i]);
	free(path_chunks);
}

char	*get_path(char *cmd, int join)
{
	int		i;
	int		j;
	char	**path_chunks;
	char	*cmd_joined_path;

	i = 0;
	if (join == 1)
		cmd = ft_strjoin(ft_strdup("/"), cmd);
	path_chunks = ft_split(ft_get_env("PATH"), ':');
	if (path_chunks == NULL)
		return (NULL);
	while (path_chunks[i])
	{
		cmd_joined_path = ft_strjoin(ft_strdup(path_chunks[i]), cmd);
		if (access(cmd_joined_path, F_OK) == 0)
		{
			j = -1;
			while (path_chunks[++j])
				free(path_chunks[j]);
			free(path_chunks);
			return (cmd_joined_path);
		}
		free(cmd_joined_path);
		i++;
	}
	get_path_free(path_chunks);
	return (NULL);
}
