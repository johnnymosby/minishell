/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/18 16:16:01 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_if_not_null(void *data)
{
	if (data != NULL)
		free(data);
}

void	clean_exit(t_shell *shell)
{
	free_if_not_null(shell->prompt);
	rl_clear_history();
	exit (shell->exit_code);
}

void	exit_if_true(t_shell *shell, int if_true)
{
	if (if_true == TRUE)
		clean_exit(shell);
}
