/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:16:01 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/08 15:19:49 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int argc, char **argv, char **envs)
{
	t_shell	shell;

	check_argc(argc);
	init_minishell(&shell, argc, argv, envs);
	minishell_loop(&shell);
	return (EXIT_SUCCESS);
}
