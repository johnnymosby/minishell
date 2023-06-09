/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:07:34 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/29 17:12:16 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute(t_shell *shell)
{
	g_status = FALSE;
	if (shell->n_cmd_tbls <= 1)
		execute_without_pipes(shell);
	else
		execute_with_pipes(shell);
}
