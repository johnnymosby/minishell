/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:12 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/21 11:09:51 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_input(t_shell *shell)
{
	shell->input = readline(shell->prompt);
	if (shell->input == NULL)
		return (FALSE);
	shell->trimmed_input = ft_strtrim(shell->input, SPACES);
	if (shell->trimmed_input == NULL)
		return (FALSE);
	return (TRUE);
}

void	minishell_loop(t_shell *shell)
{
	while (1)
	{
		clean_shell(shell);
		check_signals(shell);
		exit_if_true(shell, get_input(shell) == FALSE, FT_ERROR);
		history(shell);
		if (lexer(shell) == TRUE && expander(shell) == TRUE
			&& parser(shell) == TRUE)
			execute(shell);
	}
}
