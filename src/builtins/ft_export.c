/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:25:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 18:22:03 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"

int	is_in_envs(const char *var, const char **env);
/*
Behaviour of export in bash:
export no argument prints all env variables with "declare -x " in front
export var adds var into envs if it not in evns; if var is already in envs then nothing happens
export var=something adda "var=something" into envs. If var is already in envs its value is modified. 
*/
void	print_env_variable(char *var)
{
	while (*var && *var != '=')
	{
		ft_putchar_fd(*var,  STDOUT_FILENO);
		var++;
	}
	if (*var == '=')
	{
		ft_putchar_fd(*var, STDOUT_FILENO);
		var++;
	}
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putstr_fd(var, STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int export_no_arg_value(t_shell *shell, char *var)
{
	int	i;

	i = 0;
	if (!var)
	{
		while (shell->envs[i])
		{
			print_env_variable(shell->envs[i]);
			i++;
		}
	}
	return (0);
}

char	*get_env_var_name(t_shell *shell, char *var)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (shell->envs[i])
	{
		if(is_in_envs(shell->envs[i], var))
		{
			s = ft_substr(var, i, ft_strchr(var, =));
			if (!s)
			{
				free(var);
				clean_exit(shell, FT_ERROR);
			}
			return (s);
		}
		i++;
	}
	return (NULL);
}

int	ft_export(t_shell *shell, char **args)
{
	int		p;
	int		i;
	char	*name;
	char	*value;

	if (!args )
	p =	export_no_arg_value(shell,  *args);
	if (nb_of_rows(args) >= 1)
	{
		i = 0;
		while (args[i])
		{
			if (!ft_strchr(args[i], "=") && !is_in_envs(args[i], shell->envs))
				add_new_env(ars[i], shell); 
			else if (ft_strchr(args[i], "=") && is_in_envs(args[i], shell->envs))
			{
				name = get_env_var_name(shell, args[i]);
				value = ft_strchr(args[i]);
				construct_env_var(name, value, TRUE, shell);
			}
			else
				cmd->envs = ft_add_line(shell->envs, args[i]);
			i++;
		} 
	}
	return (0);
}
