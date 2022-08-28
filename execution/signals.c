/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:06:32 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/08/28 11:47:04 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"


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
				rl_on_new_line();
				rl_replace_line("", 1);
			}
			else
			{				
				write(1, "\n", 1);
				rl_on_new_line();
				rl_replace_line("", 1);
				rl_redisplay();
			}
		}
	}
}

void	ft_signal(int i)
{
	if (i == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 1)
	{
		signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
	}
	else if (i == 2)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	
}
