/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:53 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/22 15:23:25 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	lexer_loop(t_shell *shell)
// {
// 	while ()
// 	{
		
// 	}
// }

int	lexer(t_shell *shell)
{
	if (shell->trimmed_input[0] == '\0')
		return (FALSE);
	init_tkn_tbl(shell);
	//lexer_loop(shell);
	return (TRUE);
}
