/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:40:35 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/08 15:28:41 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_minishell(t_shell *shell, int argc, char **argv, char **envs)
{
	shell->argc = argc;
	shell->argv = argv;
	shell->envs = envs;
	shell->prompt = "prompt 😀: ";
}
