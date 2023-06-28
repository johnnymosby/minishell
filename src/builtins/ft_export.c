/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:25:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/28 13:20:27 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	process_arg(t_shell *shell, char **args, int i)
{
	char	*name;
	int		index;

	if (ft_strchr(args[i], '='))
	{
		if (is_in_envs(args[i], shell->envs) == FALSE)
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
}

int	ft_export(t_shell *shell, char **args)
{
	int		i;

	if (!args || !*args)
		return (ft_env(shell, args));
	i = 0;
	while (args[i])
	{
		if (is_valid_identifier("export", args[i]) == FALSE)
		{
			write_identifier_error_message("export", args[i]);
			i++;
			continue ;
		}
		process_arg(shell, args, i);
		i++;
	}
	return (0);
}
