/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:16:01 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/27 17:33:22 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*construct_env_var(const char *name, char *value, int to_free_value,
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

static void	change_env_value(const char *name, char *value, int to_free_value,
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

static void	set_new_value(char *name, char *value, int to_free_value,
		t_shell *shell)
{
	char	*env_var;

	if (is_in_envs(name, shell->envs) == FALSE)
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

/*
Changes the current working directory
*/
int	ft_cd(t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	if (!cmd_tbl->args || (ft_strcmp(cmd_tbl->args[0], "~") == 0
			&& cmd_tbl->args[1] == NULL))
		return (go_to_home(shell));
	else if ((ft_strcmp(cmd_tbl->args[0], "~") == 0
			&& cmd_tbl->args[1] != NULL))
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		if (!ft_strcmp(cmd_tbl->args[0], "-"))
			return (go_to_old_dir(shell));
		else
			return (go_to_dir(cmd_tbl->args[0], shell));
	}
}
