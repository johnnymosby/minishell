/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:57:51 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/01 18:20:17 by rbasyrov         ###   ########.fr       */
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
		free_input(shell);
		free_tkn_tbl(&shell->tkn_tbl);
	}
}
