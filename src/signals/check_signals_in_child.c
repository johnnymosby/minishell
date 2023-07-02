/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signals_in_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:37:46 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/07/02 11:43:40 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_sigint_in_child(void)
{
	struct sigaction	sigint;

	sigemptyset(&sigint.sa_mask);
	sigint.sa_handler = SIG_DFL;
	sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigint, NULL);
}

void	check_signals_in_child(struct termios *mirror_termios)
{
	tcsetattr(1, TCSAFLUSH, mirror_termios);
	signal(SIGQUIT, SIG_IGN);
	handle_sigint_in_child();
}
