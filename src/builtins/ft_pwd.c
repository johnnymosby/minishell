/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:46:26 by maruzibo          #+#    #+#             */
/*   Updated: 2023/07/02 12:03:08 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
This function prints the address of currenct directory 
*/
int	ft_pwd(t_shell *shell)
{
	char	path[FT_PATH_MAX];

	if (getcwd(path, sizeof(path)))
		ft_putendl_fd(path, STDOUT_FILENO);
	else if (is_in_envs("PWD", shell->envs) == TRUE)
	{
		ft_putstr_fd(shell->envs[return_env_var_index("PWD", shell->envs)] + 4,
			STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		perror("getcwd() error");
		return (1);
	}
	return (0);
}
