/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:17:40 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/29 17:37:54 by rbasyrov         ###   ########.fr       */
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

static void	save_termios_settings(t_shell *shell)
{
	struct termios	termios_settings;

	tcgetattr(1, &(shell->termios));
	tcgetattr(1, &termios_settings);
	tcsetattr(1, TCSAFLUSH, &termios_settings);
}

void	check_signals(t_shell *shell)
{
	g_status = FALSE;
	save_termios_settings(shell);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
