/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:40:47 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 17:24:26 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_last_heredoc_in_cmd(t_tkn_tbl *tkn_tbl, int i)
{
	int	last_heredoc_ind;

	last_heredoc_ind = -1;
	while (i != tkn_tbl->n_tkns && tkn_tbl->tkns[i].type != FT_PIPE)
	{
		if (tkn_tbl->tkns[i].type == FT_DLESS)
			last_heredoc_ind = i;
		i++;
	}
	return (last_heredoc_ind);
}

int	skip_cmd(t_tkn_tbl *tkn_tbl, int i)
{
	while (i != tkn_tbl->n_tkns && tkn_tbl->tkns[i].type != FT_PIPE)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
			return (i + 1);
		i++;
	}
	return (i);
}
