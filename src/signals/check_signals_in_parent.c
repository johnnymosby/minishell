/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signals_in_parent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:37:19 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/30 15:31:34 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_sigint_in_parent(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	check_signals_in_parent(struct termios *termios)
{
	struct sigaction	sigint;

	sigemptyset(&sigint.sa_mask);
	sigint.sa_handler = handle_sigint_in_parent;
	sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigint, NULL);
}
