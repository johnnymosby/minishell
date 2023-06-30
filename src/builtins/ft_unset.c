/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:19:40 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/30 17:35:52 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
Unset without options
*/
int	ft_unset(t_shell *shell, char **args)
{
	int		i;
	int		index;

	if (args == NULL || args[0] == NULL || shell->envs == NULL)
		return (0);
	i = 0;
	while (args[i] != NULL)
	{
		if (is_valid_identifier("unset", args[i]) == FALSE)
		{
			write_identifier_error_message("unset", args[i]);
			i++;
			continue ;
		}
		index = return_env_var_index(args[i], shell->envs);
		if (index < 0)
		{
			i++;
			continue ;
		}
		remove_env_variable(shell, index);
		i++;
	}
	return (0);
}
