/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_with_filepaths.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:46:00 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 17:53:58 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*extract_folder(const char *path, int n, t_shell *shell)
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
		clean_exit(shell, FT_ERROR);
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

static char	*get_next_folder_from_path(const char *path, int i, t_shell *shell)
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

static int	command_is_in_folder(DIR *dir, char *cmd)
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

char	*find_folder_with_command(char *cmd, const char *path,
	t_shell *shell)
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
				exit_if_true(shell, TRUE, FT_ERROR);
			}
			if (command_is_in_folder(dir, cmd) == TRUE)
				return (folder);
		}
		free(folder);
		i++;
		folder = get_next_folder_from_path(path, i, shell);
	}
	return (set_exit_code(shell, 127), NULL);
}

int	is_directory(char *cmd, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode) == 0)
			return (FALSE);
		else
			return (TRUE);
	}
	clean_exit(shell, FT_ERROR);
	return (FALSE);
}
