/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:25:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 19:22:03 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_var_name(t_shell *shell, char *var)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	while (var[j] && var[j] != '=')
		j++;
	s = ft_substr(var, 0, j);
	if (!s)
	{
		free(var);
		clean_exit(shell, FT_ERROR);
	}
	return (s);
	i++;
	return (NULL);
}

int	return_env_var_index(char *var, char **env)
{
	int	i;
	int	n;

	if (!var || !env)
		return (-1);
	n = 0;
	while (var[n] != '\0' && var[n] != '=')
		n++;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, n))
			return (i);
		i++;
	}
	return (-1);
}

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
