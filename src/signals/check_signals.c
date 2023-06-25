/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:17:40 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 16:41:47 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_status == NOCMD_NOSIG || g_status == NOCMD_SIG)
			g_status = NOCMD_SIG;
		else if (g_status == CMD_NOSIG || g_status == CMD_SIG)
			g_status = CMD_SIG;
		if (g_status == HEREDOC)
		{
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		}
		else
			write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_status == NOCMD_SIG)
			rl_redisplay();
		if (g_status == HEREDOC)
			g_status = NOCMD_SIG;
	}
}

void	check_signals(t_shell *shell)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
