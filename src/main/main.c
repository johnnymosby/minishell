/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:16:01 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/28 13:20:37 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envs)
{
	t_shell	*shell;

	if (argc > 1)
		return (ft_putstr_fd("The program does not take any arguments\n",
				STDERR_FILENO), 1);
	(void)argv;
	g_status = NOCMD_NOSIG;
	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	init_minishell(shell, envs);
	minishell_loop(shell);
	return (EXIT_SUCCESS);
}
