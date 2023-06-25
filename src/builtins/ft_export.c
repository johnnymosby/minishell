/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:25:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 22:44:11 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export(t_shell *shell, char **args)
{
	int		i;
	char	*name;
	int		index;

	if (!args || !*args)
		ft_env(shell);
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (!is_in_envsv(args[i], shell->envs))
			{
				add_new_env(args[i], shell);
				args[i] = NULL;
			}
			else
			{
				name = get_env_var_name(shell, args[i]);
				index = return_env_var_index(name, shell->envs);
				free(name);
				free(shell->envs[index]);
				shell->envs[index] = args[i];
				args[i] = NULL;
			}
		}
		i++;
	}
	return (0);
}
