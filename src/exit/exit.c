/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/22 15:59:08 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tkn_tbl(t_tkn_tbl **tkn_tbl)
{
	int		i;
	t_tkn	**tkns;
	int		n_tkns;

	if (*tkn_tbl != NULL && (*tkn_tbl)->tkns != NULL)
	{
		i = 0;
		tkns = &((*tkn_tbl)->tkns);
		n_tkns = (*tkn_tbl)->n_tkns;
		while (i != n_tkns)
		{
			free_if_not_null((void **)&(*tkns[i]->cntnt));
			i++;
		}
		free_if_not_null((void **)tkns);
	}
	free_if_not_null((void **)tkn_tbl);
}

void	clean_exit(t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_code;
	free_tkn_tbl(&shell->tkn_tbl);
	free_if_not_null((void **)&shell->trimmed_input);
	free_if_not_null((void **)&shell->prompt);
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
