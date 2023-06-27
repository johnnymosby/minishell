/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_a_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:49:02 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/27 17:20:09 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	change_dir_to_home(t_shell *shell)
{
	char	*home;
	char	*var;
	char	*oldpwd_val;

	var = ft_strdup("HOME");
	exit_if_true(shell, var == NULL, FT_ERROR);
	home = find_env_value(shell->envs, var, 4, shell);
	free(var);
	if (home == NULL)
		return (FALSE);
	oldpwd_val = getcwd(NULL, FT_PATH_MAX);
	if (oldpwd_val == NULL)
		clean_exit(shell, FT_ERROR);
	if (chdir(home) == -1)
	{
		free(oldpwd_val);
		write_file_error_message("chdir");
		return (FALSE);
	}
	else
		return (change_pwd_and_oldpwd(oldpwd_val, shell), TRUE);
}

int	go_to_home(t_shell *shell)
{
	if (is_in_envs("HOME", shell->envs) == FALSE)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (FALSE);
	}
	else
	{
		if (change_dir_to_home(shell) == FALSE)
			return (FALSE);
		else
			return (TRUE);
	}
}

int	go_to_old_dir(t_shell *shell)
{
	char	*value;
	char	*oldpwd_val;
	char	*pwd_val;

	if (is_in_envs("OLDPWD", shell->envs) == FALSE)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (FALSE);
	}
	value = find_env_value(shell->envs, "OLDPWD", 6, shell);
	if (value[0] == '\0')
		return (ft_putstr_fd("\n", STDIN_FILENO), TRUE);
	oldpwd_val = getcwd(NULL, FT_PATH_MAX);
	if (oldpwd_val == NULL)
		clean_exit(shell, FT_ERROR);
	if (chdir(value) == -1)
		return (write_file_error_message(value), FALSE);
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
