/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_pathname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:12:14 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 18:03:34 by rbasyrov         ###   ########.fr       */
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

char	*construct_pathname(char *cmd, t_shell *shell)
{
	char	*pathname;
	char	*folder;
	int		path_ind;

	if (strchr(cmd, '/') != NULL)
		return (return_cmd_as_pathname(cmd, shell));
	path_ind = 0;
	while (shell->envs[path_ind] != NULL)
	{
		if (ft_strncmp(shell->envs[path_ind], "PATH=", 5) == 0)
			break ;
		path_ind++;
	}
	if (shell->envs[path_ind] == NULL)
		return (set_exit_code(shell, 1), NULL);
	folder = find_folder_with_command(cmd, shell->envs[path_ind], shell);
	if (folder == NULL)
		return (print_command_not_found(cmd), NULL);
	pathname = ft_strjoin(folder, cmd);
	free(folder);
	if (pathname == NULL)
		print_error_and_exit(shell);
	return (pathname);
}
