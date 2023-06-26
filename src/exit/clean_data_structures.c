/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data_structures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:44:11 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 18:46:10 by rbasyrov         ###   ########.fr       */
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
			free_if_not_null((void **)&(tkns[0][i].cntnt));
			i++;
		}
		free_if_not_null((void **)tkns);
	}
	free_if_not_null((void **)tkn_tbl);
}

void	free_cmd_tbls(t_cmd_tbl **cmd_tbls, int n)
{
	int			i;
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = *cmd_tbls;
	if (cmd_tbl != NULL)
	{
		i = 0;
		while (i != n)
		{
			free_cmd_tbl(&cmd_tbl[i]);
			i++;
		}
	}
	free_if_not_null((void **)cmd_tbls);
}
