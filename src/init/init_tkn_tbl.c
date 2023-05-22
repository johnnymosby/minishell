/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tkn_tbl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:15:29 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/22 16:15:10 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	increase_tkn_tbl(t_shell *shell)
{
	int			old_max;
	int			new_max;
	t_tkn_tbl	*new_t_tkn;
	int			i;

	old_max = shell->tkn_tbl->max_n_tkns;
	new_max = (int)(1.5 * old_max);
	new_t_tkn = ft_calloc(1, new_max);
	if (new_t_tkn == NULL)
		clean_exit(shell);
	i = 0;
	new_t_tkn->max_n_tkns = new_max;
	new_t_tkn->n_tkns = old_max;
	while (i != old_max)
	{
		new_t_tkn->tkns[i] = shell->tkn_tbl->tkns[i];
		i++;
	}
}

void	init_tkn_tbl(t_shell *shell)
{
	shell->tkn_tbl = ft_calloc(1, sizeof(t_tkn_tbl));
	if (shell->tkn_tbl == NULL)
		clean_exit(shell);
	shell->tkn_tbl->max_n_tkns = 16;
	shell->tkn_tbl->tkns = ft_calloc(shell->tkn_tbl->n_tkns, sizeof(t_tkn));
	if (shell->tkn_tbl->tkns == NULL)
		clean_exit(shell);
}
