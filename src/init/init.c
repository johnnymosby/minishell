/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:40:35 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/09 19:01:34 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
**exit the program if STDIN_FILENO does not refer to a terminal device
**initialise arguments
*/
void	init_minishell(t_shell *shell, char **envs)
{
	if (!isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	shell->envs = envs;
	shell->prompt = "prompt 😀: ";
}
