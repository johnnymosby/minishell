/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:16:01 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/07 13:09:25 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int argc, char **argv, char **envs)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	init_minishell(shell, envs);
	minishell_loop(shell);
	return (EXIT_SUCCESS);
}
