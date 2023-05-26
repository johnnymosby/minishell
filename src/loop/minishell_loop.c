/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:12 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/26 15:16:12 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_input(t_shell *shell)
{
	free_if_not_null((void **)&shell->input);
	free_if_not_null((void **)&shell->trimmed_input);
}

static int	get_input(t_shell *shell)
{
	free_input(shell);
	shell->input = readline(shell->prompt);
	if (shell->input == NULL)
		return (FALSE);
	shell->trimmed_input = ft_strtrim(shell->input, SPACES);
	if (shell->trimmed_input == NULL)
		return (FALSE);
	return (TRUE);
}

//check signals
//read line
void	minishell_loop(t_shell *shell)
{
	while (1)
	{
		check_signals(shell);
		exit_if_true(shell, get_input(shell) == FALSE, FT_NOT_ERROR);
		// update environment
		if (lexer(shell) == TRUE && expander(shell) == TRUE
			&& parser(shell) == TRUE)
			execute(shell);
		printf("%s\n", shell->input);
		history(shell);
	}
}
