/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:29:06 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 12:28:39 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_all_spaces(t_tkn_tbl *tkn_tbl, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[i].type == FT_SPACE && (i + 1) != tkn_tbl->n_tkns)
		{
			shift_array_by_one_to_left(tkn_tbl, i);
			tkn_tbl->n_tkns -= 1;
		}
		else
			i++;
	}
}

int	parser(t_shell *shell)
{
	concatenate_words(shell->tkn_tbl, shell);
	remove_all_spaces(shell->tkn_tbl, shell);
	if (check_syntax(shell->tkn_tbl, shell) == FALSE)
		return (FALSE);
	construct_cmd_tables(shell->tkn_tbl, shell);
	if (handle_heredocs(shell->tkn_tbl, shell->cmd_tbls, shell) == FALSE)
		return (FALSE);
	return (TRUE);
}
