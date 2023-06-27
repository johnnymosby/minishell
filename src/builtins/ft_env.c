/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:38:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/27 17:37:19 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_shell *shell, char **args)
{
	int		i;

	if (args != NULL)
	{
		ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while (shell->envs[i])
	{
		ft_putendl_fd(shell->envs[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
