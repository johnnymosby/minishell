/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:12 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/18 16:28:40 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//check signals
//read line

static int	get_input(t_shell *shell)
{
	shell->input = readline(shell->prompt);
	if (shell->input == NULL)
		return (FALSE);
	shell->trimmed_input = ft_strtrim(shell->input, SPACES);
	return (TRUE);
}

void	minishell_loop(t_shell *shell)
{
	while (1)
	{
		check_signals(shell);
		if (get_input(shell) == FALSE)
			clean_exit(shell);
		// update environment	
		if (lexer(shell) == TRUE && parser(shell) == TRUE)
			execute(shell);
		printf("%s\n", shell->input);
		history(shell);
	}
}
