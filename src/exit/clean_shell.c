/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:57:51 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/14 13:11:58 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_input(t_shell *shell)
{
	free_if_not_null((void **)&shell->input);
	free_if_not_null((void **)&shell->trimmed_input);
}

void	clean_shell(t_shell *shell)
{
	if (shell != NULL)
	{
		free_cmd_tbls(&shell->cmd_tbls, shell->n_cmd_tbls);
		free_tkn_tbl(&shell->tkn_tbl);
		free_input(shell);
	}
}
