/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:16:01 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/23 16:41:03 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_in_envs(const char *var, const char **env)
{
	int	i;
	int	n;

	if (!var || !env)
		return (FALSE);
	n = ft_strchr(var, '=') - var;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, n + 1))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	add_new_env(char *env_var, t_shell *shell)
{
	int		len;
	int		i;
	char	**new_envs;

	len = 0;
	while (shell->envs[len] != NULL)
		len++;
	new_envs = ft_calloc(len + 2, sizeof(char *));
	if (new_envs == NULL)
	{
		free(env_var);
		clean_exit(shell, FT_ERROR);
	}
	i = 0;
	while (i != len)
	{
		new_envs[i] = shell->envs[i];
		i++;
	}
	new_envs[i] = env_var;
	new_envs[i + 1] = NULL;
	free(shell->envs);
	shell->envs = new_envs;
}

char	*construct_env_var(const char *name, char *value, int to_free_value,
	t_shell *shell)
{
	char	*env_var_with_sign;
	char	*env_var;

	env_var_with_sign = ft_strjoin(name, "=");
	if (env_var_with_sign == NULL)
	{
		if (to_free_value == TRUE)
			free(value);
		clean_exit(shell, FT_ERROR);
	}
	env_var = ft_strjoin(env_var_with_sign, value);
	free(env_var_with_sign);
	if (env_var == NULL)
	{
		if (to_free_value == TRUE)
			free(value);
		clean_exit(shell, FT_ERROR);
	}
	return (env_var);
}

void	change_env_value(const char *name, char *value, int to_free_value,
	t_shell *shell)
{
	int		i;
	char	*env_var;

	i = 0;
	while (shell->envs[i] != NULL && ft_strncmp(name, shell->envs[i],
			ft_strlen(name)) != 0)
		i++;
	if (shell->envs[i] == NULL)
	{
		if (to_free_value == TRUE)
			free(value);
		clean_exit(shell, FT_ERROR);
	}
	env_var = construct_env_var(name, value, to_free_value, shell);
	free(shell->envs[i]);
	shell->envs[i] = env_var;
}

void	set_new_value(const char *name, char *value, int to_free_value,
	t_shell *shell)
{
	char	*env_var;

	if (is_in_envs(name, (const char **)shell->envs) == FALSE)
	{
		env_var = construct_env_var(name, value, to_free_value, shell);
		add_new_env(env_var, shell);
	}
	else
		change_env_value(name, value, to_free_value, shell);
}

void	change_pwd_and_oldpwd(char *oldpwd_val, t_shell *shell)
{
	char	*pwd_val;

	set_new_value("OLDPWD", oldpwd_val, TRUE, shell);
	free(oldpwd_val);
	pwd_val = getcwd(NULL, FT_PATH_MAX);
	if (pwd_val == NULL)
	{
		free(pwd_val);
		clean_exit(shell, FT_ERROR);
	}
	set_new_value("PWD", pwd_val, TRUE, shell);
	free(pwd_val);
}

int	go_to_home(t_shell *shell)
{
	char	*home;
	char	*var;
	char	*oldpwd_val;

	if (!is_in_envs("HOME", (const char **)shell->envs))
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
		oldpwd_val = getcwd(NULL, FT_PATH_MAX);
		if (oldpwd_val == NULL)
		{
			free(home);
			clean_exit(shell, FT_ERROR);
		}
		if (chdir(home) == -1)
		{
			free(home);
			free(oldpwd_val);
			write_file_error_message("cmd");
			return (FALSE);
		}
		else
		{
			free(home);
			change_pwd_and_oldpwd(oldpwd_val, shell);
			return (TRUE);
		}
	}
}

int	go_to_old_dir(t_shell *shell)
{
	char	*value;
	char	*oldpwd_val;
	char	*pwd_val;

	if (is_in_envs("OLDPWD", (const char **)shell->envs) == FALSE)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (FALSE);
	}
	value = find_env_value(shell->envs, "OLDPWD", 6, shell);
	if (value[0] == '\0')
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		return (TRUE);
	}
	oldpwd_val = getcwd(NULL, FT_PATH_MAX);
	if (oldpwd_val == NULL)
		clean_exit(shell, FT_ERROR);
	if (chdir(value) == -1)
	{
		write_file_error_message(value);
		return (FALSE);
	}
	change_pwd_and_oldpwd(oldpwd_val, shell);
	return (TRUE);
}

int	go_to_dir(char *pathname, t_shell *shell)
{
	char	*oldpwd_val;

	oldpwd_val = getcwd(NULL, FT_PATH_MAX);
	if (oldpwd_val == NULL)
		clean_exit(shell, FT_ERROR);
	if (chdir(pathname) == -1)
	{
		free(oldpwd_val);
		write_file_error_message("cmd");
		return (FALSE);
	}
	change_pwd_and_oldpwd(oldpwd_val, shell);
	return (TRUE);
}

/*
Changes the current working directory
*/
int	ft_cd(t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	if (!cmd_tbl->args)
		return (go_to_home(shell));
	else
	{
		if (!ft_strcmp(cmd_tbl->args[0], "-"))
			return (go_to_old_dir(shell));
		else
			return (go_to_dir(cmd_tbl->args[0], shell));
	}
}
