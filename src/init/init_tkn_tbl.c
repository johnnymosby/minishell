/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tkn_tbl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:15:29 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/22 15:42:12 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
