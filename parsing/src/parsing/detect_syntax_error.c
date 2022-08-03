/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmaidi <ahmaidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:46 by ahmaidi           #+#    #+#             */
/*   Updated: 2022/07/29 16:14:28 by ahmaidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error(void)
{
	printf("syntax eroor \n");
	exit(1);
}

void	detect_syntax_error(char *s)
{
	int	i;
	int	nb_d_q;
	int	nb_s_q;

	i = 0;
	nb_d_q = 0;
	nb_s_q = 0;
	while (s[i])
	{
		if (s[i] == S_QOUTE)
			nb_s_q++;
		if (s[i] == D_QOUTE)
			nb_d_q++;
		i++;
	}
	if (*s == D_QOUTE && s[i - 1] == D_QOUTE)
		if (nb_d_q % 2 != 0)
			error();
	if (*s == S_QOUTE && s[i - 1] == S_QOUTE)
		if (nb_s_q % 2 != 0)
			error();
	if ((*s == D_QOUTE && s[i - 1] == S_QOUTE)
		|| (*s == D_QOUTE && s[i - 1] == S_QOUTE))
	{
		if (nb_d_q % 2 != 0 || nb_s_q % 2 != 0)
			error();
	}
	else
		error();
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		detect_syntax_error(argv[1]);
	while (1)
	{
		printf("minishell$ \n");
		while (1)
			;
	}
}
