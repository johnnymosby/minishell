/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:07:34 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 18:17:23 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute(t_shell *shell)
{
	g_status = CMD_NOSIG;
	if (shell->n_cmd_tbls <= 1)
		execute_without_pipes(shell);
	else
		execute_with_pipes(shell);
}
