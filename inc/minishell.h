/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:13:56 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/19 15:32:55 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "structs.h"
# include "defines.h"
// macros:		EXIT_SUCCESS, EXIT_FAILURE
// functions:	exit, getenv
# include <stdlib.h>

// functions:	printf, perror
# include <stdio.h>

// macros:		STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO
// functions:	execve
# include <unistd.h>

// functions:	readline
# include <readline/readline.h>

// macros:		SIGINT, SIGQUIT, SIG_IGN
// functions:	signal
# include <signal.h>

// functions:	rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
				//add_history
# include <readline/history.h>

# include <sys/ioctl.h>
# include <termios.h>
// main/...
//	 .../main.c

// utils/...
//		.../general_utils.c
void	free_if_not_null(void **data);
//		.../history.c
void	history(t_shell *shell);

// signals/...
//	 .../check_signals.c
void	check_signals(t_shell *shell);

// loop/...
//	 .../minishell_loop.c
void	minishell_loop(t_shell *shell);

// init/...
//	 .../init.c
void	init_minishell(t_shell *shell, char **envs);

// lexer/...
//	 .../lexer.c
int		lexer(t_shell *shell);

// parser/...
//	 .../parser.c
int		parser(t_shell *shell);

// execute/...
//	 .../execute.c
int		execute(t_shell *shell);
int		execute_cmd(t_shell *shell, t_cmd_table *cmd_tb);

// 	exit/...
//	 .../exit.c
void	clean_exit(t_shell *shell);
void	exit_if_true(t_shell *shell, int if_true);

#endif