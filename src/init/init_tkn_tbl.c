/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tkn_tbl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:15:29 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/24 23:56:03 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	increase_tkn_tbl(t_shell *shell)
{
	int			old_max;
	int			new_max;
	t_tkn_tbl	*new_tkn_tbl;
	int			i;

	old_max = shell->tkn_tbl->max_n_tkns;
	new_max = (int)(1.5 * old_max);
	new_tkn_tbl = ft_calloc(1, sizeof(t_tkn_tbl));
	if (new_tkn_tbl == NULL)
	{
		ft_putstr_fd("minishell: calloc failed with new_tkn_tbl", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	new_tkn_tbl->tkns = ft_calloc(new_max, sizeof(t_tkn));
	if (new_tkn_tbl->tkns == NULL)
	{
		free(new_tkn_tbl);
		ft_putstr_fd("minishell: calloc failed with new_tkn_tbl->tkns", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	i = -1;
	while (++i != old_max)
		new_tkn_tbl->tkns[i] = shell->tkn_tbl->tkns[i];
	new_tkn_tbl->max_n_tkns = new_max;
	new_tkn_tbl->n_tkns = old_max;
	free(shell->tkn_tbl->tkns);
	free(shell->tkn_tbl);
	shell->tkn_tbl = new_tkn_tbl;
}

void	init_tkn_tbl(t_shell *shell)
{
	shell->tkn_tbl = ft_calloc(1, sizeof(t_tkn_tbl));
	if (shell->tkn_tbl == NULL)
	{
		ft_putstr_fd("minishell: calloc failed with shell->tkn_tbl\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	shell->tkn_tbl->max_n_tkns = 4;
	shell->tkn_tbl->tkns = ft_calloc(shell->tkn_tbl->max_n_tkns, sizeof(t_tkn));
	if (shell->tkn_tbl->tkns == NULL)
	{

		ft_putstr_fd("minishell: calloc failed with new_tkn_tbl->tkns", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
}
