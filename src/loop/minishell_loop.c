/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:42:12 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/08 17:00:14 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//check signals
//read line

void	minishell_loop(t_shell *shell)
{
	char	*user_input;

	while (1)
	{
		check_signals(shell);
		user_input = readline(shell->prompt);
		if (user_input == NULL)
			break ;
		printf("%s\n", user_input);
		user_input = NULL;
	}
}
