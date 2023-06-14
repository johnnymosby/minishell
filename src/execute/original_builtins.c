/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   original_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:12:14 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/14 15:13:35 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_path_variable(char **envs)
{
	int	i;

	i = 0;
	while (envs[i] != NULL)
	{
		if (ft_strncmp(envs[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_folder(const char *path, int n,  t_shell *shell)
{
	int		len;
	char	*folder;
	int		i;

	len = 0;
	while (path[n + len] != '\0' && path[n + len] != ':')
		len++;
	folder = malloc(sizeof(char) * (len + 2));
	if (folder == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		clean_exit(shell, TRUE);
	}
	i = 0;
	while (i != len)
	{
		folder[i] = path[n + i];
		i++;
	}
	folder[i] = '/';
	folder[i + 1] = '\0';
	return (folder);
}

char *get_next_folder_from_path(const char *path, int i, t_shell *shell)
{
	int		j;
	int		n;

	j = 0;
	n = 0;
	while (path[n] != '\0')
	{
		if (path[n] == '/')
			break ;
		n++;
	}
	while (j < i && path[n] != '\0')
	{
		if (path[n] == ':')
			j++;
		n++;
	}
	if (j != i)
		return (NULL);
	else
		return (extract_folder(path, n, shell));
}

int	command_is_in_folder(DIR *dir, char *cmd)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, cmd) == 0)
			return (closedir(dir), TRUE);
		entry = readdir(dir);
	}
	closedir(dir);
	return (FALSE);
}

char	*find_folder_with_command(char *cmd, const char *path, t_shell *shell)
{
	DIR				*dir;
	char			*folder;
	int				i;

	i = 0;
	folder = get_next_folder_from_path(path, i, shell);
	while (folder != NULL)
	{
		if (access(folder, X_OK) != -1)
		{
			dir = opendir(folder);
			if (dir == NULL)
			{
				write_file_error_message(folder);
				free(folder);
				clean_exit(shell, TRUE);
			}
			if (command_is_in_folder(dir, cmd) == TRUE)
				return (folder);
		}
		free(folder);
		i++;
		folder = get_next_folder_from_path(path, i, shell);
	}
	return (NULL);
}

char	*construct_pathname(char *cmd, t_shell *shell)
{
	char	*pathname;
	char	*folder;
	int		path_ind;

	path_ind = find_path_variable(shell->envs);
	if (path_ind < 0)
		return (NULL);
	folder = find_folder_with_command(cmd, shell->envs[path_ind], shell);
	if (folder == NULL)
		return (NULL);
	pathname = ft_strjoin(folder, cmd);
	free(folder);
	if (pathname == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		clean_exit(shell, TRUE);
	}
	return (pathname);
}