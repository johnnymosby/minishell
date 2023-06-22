/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:16:01 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/22 23:43:14 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**set_new_env_var(char **env, char *var, char *value)
{
	int		i[2];
	char	*str;
	char	*tmp;

	if (ft_strchr(var, '=') || !var)
		return (NULL);
	str = join_with_equal(var, value);
	i[0] = 0;
	while (env && env[i[0]])
	{
		i[1] = ft_strlen(var);
		if (!ft_strncmp(env[i[0]], var, i[1])
			&& env[i[0]][i[1]] == '=')
		{
			tmp = env[i[0]];
			env[i[0]] = str;
			free(tmp);
			return (env[i[0]]);
		}
		i[0]++;
	}
	env = ft_add_line(env, str);
	free(str);
	return (env);
}

/*
This function changes the address of the dicrectory: 
old and current dicrectory addresses are updated
*/
int	change_address(char **env, char *new)
{
	char	s[MAX_PATH];

	if (!getcwd(s, MAX_PATH))
		return (2); //why 2?
	if (!is_in_envs("PWD", env))
		ft_set_new_env(env, "PWD", s);
	s = ft_getenv(env, "PWD");
	ft_set_new_env(env, "PWD", new);
	if (!is_in_envs("OLDPWD", cmd->env))
		ft_set_new_env(cmd, "OLDPWD", s);
	ft_set_new_env(env, "OLDPWD", s);
	return (0);
}

int	go_to_home(t_shell *shell)
{
	char	*home;
	char	*var;

	if (!is_in_envs("HOME", shell->envs))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (FALSE);
	}
	else
	{
		var = ft_strdup("cmd");
		exit_if_true(shell, var == NULL, FT_ERROR);
		home = find_env_value(shell->envs, var, 3, shell);
		free(var);
		exit_if_true(shell, home == NULL, FT_ERROR);
		if (!chdir(home) && change_address(shell->envs, "HOME") == FALSE)
			code = ;
		else
		{
			write_file_error_message("cmd");
			shell->exit_code = 1;
		}
	}
	if (home)
		free(home);
	return (code);
}

int	is_in_envs(char *var, char **env)
{
	int	i;
	int	n;

	if (!var || !env)
		return (-1);
	n = ft_strchr(var, '=');
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, n + 1))
			return (i);
		i++;
	}
	return (-1);
}

int	go_to_old_dir(t_shell *shell)
{
	char	*value;

	if (!is_in_envs("OLDPWD", shell->envs))
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (FALSE);
	}
	value = find_env_value(shell->envs, "OLDPWD", 6, shell);
	if (value[0] == '\0')
	{
		free(value);
		ft_putstr_fd("\n", STDIN_FILENO);
		return (TRUE);
	}
	if (chdir(value) == -1)
	{
		write_file_error_message(value);
		free(value)
		return (FALSE);
	}
	swap_env_var_values()
	return (TRUE);
}

/*
Changes the current working directory
*/
int	ft_cd(t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	if (!cmd_tbl->args)
		go_to_home(shell);
	else
	{
		if (!ft_strcmp(cmd_tbl->args[0], "-"))
			return (go_to_old_dir(shell));
		else if (chdir(arg) == EXIT_SUCCESS)
			change_address(cmd, pwd);
		else
			invalid_error("cd", errno, arg);
	}
}
