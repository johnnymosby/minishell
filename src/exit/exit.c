/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/19 15:35:13 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_exit(t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_code;
	free_if_not_null((void **)&shell->prompt);
	free_if_not_null((void **)&shell->trimmed_input);
	if (shell->if_history_exists == TRUE)
		rl_clear_history();
	free(shell);
	exit (exit_code);
}

void	exit_if_true(t_shell *shell, int if_true)
{
	if (if_true == TRUE)
		clean_exit(shell);
}
