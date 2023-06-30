/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:57:51 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/30 16:41:13 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	return_std_fds(t_shell *shell)
{
	dup2(shell->std_in_out[0], STDIN_FILENO);
	dup2(shell->std_in_out[1], STDOUT_FILENO);
}

void	set_exit_code(t_shell *shell, int exit_code)
{
	shell->exit_code = exit_code;
}

void	free_input(t_shell *shell)
{
	free_if_not_null((void **)&(shell->input));
	free_if_not_null((void **)&(shell->trimmed_input));
}

void	clean_shell(t_shell *shell)
{
	if (shell != NULL)
	{
		free_cmd_tbls(&shell->cmd_tbls, shell->n_cmd_tbls);
		free_tkn_tbl(&shell->tkn_tbl);
		free_input(shell);
		return_std_fds(shell);
		if (g_status == TRUE)
			shell->exit_code = 130;
		g_status = FALSE;
	}
}
