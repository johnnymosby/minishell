/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:38:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 17:09:00 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->envs[i])
	{
		ft_putendl_fd(shell->envs[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
