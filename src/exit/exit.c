/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/18 16:46:40 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_exit(t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_code;
	free_if_not_null(shell->prompt);
	free_if_not_null(shell->trimmed_input);
	rl_clear_history();
	free(shell);
	exit (exit_code);
}

void	exit_if_true(t_shell *shell, int if_true)
{
	if (if_true == TRUE)
		clean_exit(shell);
}
