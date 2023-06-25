/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:25:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 15:21:11 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env_variable(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		ft_putchar_fd(var[i], STDOUT_FILENO);
		i++;
	}
	if (var[i] == '=')
	{
		ft_putchar_fd(var[i], STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putstr_fd(var, STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void export_no_arg_value(t_shell *shell, char *var)
{
	int	i;

	i = 0;
	if (!var)
	{
		while (shell->envs[i])
		{
			//print_env_variable(shell->envs[i]);
			ft_env(shell->envs[i]);
			i++;
		}
	}
}

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

int	ft_export(t_shell *shell, char **args)
{
	int		i;
	char	*name;
	char	*value;

	if (!args || !*args)
		export_no_arg_value(shell, *args);
	if (nb_of_rows(args) >= 1)
	{
		i = 0;
		while (args[i])
		{
			if (!ft_strchr(args[i], '=') && !is_in_envsv(args[i], shell->envs))
				add_new_env(args[i], shell); 
			if (ft_strchr(args[i], '=') && is_in_envsv(args[i], shell->envs))
			{
				name = get_env_var_name(shell, args[i]);
				value = ft_strchr(args[i], '=');
				construct_env_var(name, value, TRUE, shell);
			}
			else
				shell->envs = ft_add_line(shell->envs, args[i]);
			i++;
		}
	}
	return (0);
}
