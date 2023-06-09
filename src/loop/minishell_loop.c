/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:12 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/07/02 11:40:44 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_input(t_shell *shell)
{
	if (shell->input != NULL)
		free(shell->input);
	shell->input = readline(shell->prompt);
	if (g_status == TRUE)
	{
		shell->exit_code = 130;
		g_status = FALSE;
	}
	if (shell->input == NULL)
		return (ft_putstr_fd("exit\n", STDERR_FILENO), FALSE);
	shell->trimmed_input = ft_strtrim(shell->input, SPACES);
	if (shell->trimmed_input == NULL)
		return (set_exit_code(shell, 1), FALSE);
	return (TRUE);
}

void	minishell_loop(t_shell *shell)
{
	while (1)
	{
		clean_shell(shell);
		check_signals(shell);
		exit_if_true(shell, get_input(shell) == FALSE, shell->exit_code);
		history(shell);
		if (lexer(shell) == TRUE && expander(shell) == TRUE
			&& parser(shell) == TRUE)
			execute(shell);
	}
}
