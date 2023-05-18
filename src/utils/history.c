/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:34:41 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/18 16:04:09 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// not much of code since readline incorporates the history and handling UP/DOWN

void	history(t_shell *shell)
{
	if (shell->trimmed_input[0] != '\0')
		add_history(shell->input);
}
