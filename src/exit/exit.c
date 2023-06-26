/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 18:46:27 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	delete_heredocs(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*pathname;

	if (access("/tmp/", W_OK | X_OK) == -1)
		return ;
	dir = opendir("/tmp/");
	if (dir == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, "tmp_heredoc_", 11) == 0)
		{
			pathname = ft_strjoin("/tmp/", entry->d_name);
			unlink(pathname);
			free(pathname);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

void	free_envs(t_shell *shell)
{
	int		len;
	int		i;

	if (shell->envs == NULL)
		return ;
	len = 0;
	while (shell->envs[len] != NULL)
		len++;
	i = 0;
	while (i != len)
	{
		free(shell->envs[i]);
		i++;
	}
	free(shell->envs);
}

void	clean_exit(t_shell *shell, int exit_code)
{
	free_cmd_tbls(&shell->cmd_tbls, shell->n_cmd_tbls);
	delete_heredocs();
	free_tkn_tbl(&shell->tkn_tbl);
	free_if_not_null((void **)&shell->prompt);
	free_input(shell);
	free_envs(shell);
	if (shell->if_history_exists == TRUE)
		rl_clear_history();
	close(shell->std_in_out[0]);
	close(shell->std_in_out[1]);
	free(shell);
	exit (exit_code);
}

void	exit_if_true(t_shell *shell, int if_true, int exit_code)
{
	shell->exit_code = exit_code;
	if (if_true == TRUE)
		clean_exit(shell, exit_code);
}
