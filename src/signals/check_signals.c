/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:17:40 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/30 15:32:04 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = TRUE;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static void	save_termios(t_shell *shell)
{
	struct termios	termios;

	tcgetattr(1, &(shell->termios));
	tcgetattr(1, &termios);
	tcsetattr(1, TCSAFLUSH, &termios);
}

void	check_signals(t_shell *shell)
{
	g_status = FALSE;
	save_termios(shell);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
