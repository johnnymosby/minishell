/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_pathname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:12:14 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/28 19:53:06 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_permission_denied(char *pathname)
{
	ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	print_command_not_found(char *pathname)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

static char	*return_cmd_as_pathname(char *cmd, t_shell *shell)
{
	char	*pathname;

	if (access(cmd, F_OK) != 0)
		return (write_file_error_message(cmd), NULL);
	if (is_directory(cmd, shell) == TRUE)
		return (print_permission_denied(cmd), NULL);
	pathname = ft_strdup(cmd);
	exit_if_true(shell, pathname == NULL, FT_ERROR);
	return (pathname);
}

static void	print_no_such_file(char *pathname)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

char	*construct_pathname(char *cmd, t_shell *shell)
{
	char	*pathname;
	char	*folder;
	int		path_ind;

	if (ft_strchr(cmd, '/') != NULL)
		return (return_cmd_as_pathname(cmd, shell));
	path_ind = 0;
	while (shell->envs[path_ind] != NULL)
	{
		if (ft_strncmp(shell->envs[path_ind], "PATH=", 5) == 0)
			break ;
		path_ind++;
	}
	if (shell->envs[path_ind] == NULL)
		return (print_no_such_file(cmd), NULL);
	folder = find_folder_with_command(cmd, shell->envs[path_ind], shell);
	if (folder == NULL)
		return (print_command_not_found(cmd), NULL);
	pathname = ft_strjoin(folder, cmd);
	free(folder);
	if (pathname == NULL)
		print_error_and_exit(shell);
	return (pathname);
}
