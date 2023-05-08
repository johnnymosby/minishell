/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:13:56 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/08 17:39:53 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../lib/libft/libft.h"
# include "structs.h"
// macros:		EXIT_SUCCESS, EXIT_FAILURE
// functions:	exit
# include <stdlib.h>

// functions:	printf
# include <stdio.h>
# include <unistd.h>

// functions:	readline
# include <readline/readline.h>

// macros:		SIGINT, SIGQUIT, SIG_IGN
// functions:	signal
# include <signal.h>

# include <sys/ioctl.h>
# include <termios.h>
// main/...
//	 .../main.c

// utils/...
//	 .../check_argc.c
void	check_argc(int argc);

// signals/...
//	 .../check_signals.c
void	check_signals(t_shell *shell);
// loop/...
//	 .../minishell_loop.c
void	minishell_loop(t_shell *shell);

// init/...
//	 .../init.c
void	init_minishell(t_shell *shell, int argc, char **argv, char **envs);

#endif