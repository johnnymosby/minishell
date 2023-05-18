/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:16:01 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/15 20:57:11 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int argc, char **argv, char **envs)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_minishell(&shell, envs);
	minishell_loop(&shell);
	return (EXIT_SUCCESS);
}
