/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 17:11:28 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tkn_tbl(t_tkn_tbl **tkn_tbl)
{
	int		i;
	t_tkn	**tkns;
	int		n_tkns;

	if (*tkn_tbl != NULL && (*tkn_tbl)->tkns != NULL)
	{
		i = 0;
		tkns = &((*tkn_tbl)->tkns);
		n_tkns = (*tkn_tbl)->n_tkns;
		while (i != n_tkns)
		{
			free_if_not_null((void **)&(tkns[0][i].cntnt));
			i++;
		}
		free_if_not_null((void **)tkns);
	}
	free_if_not_null((void **)tkn_tbl);
}

void	free_cmd_tbls(t_cmd_tbl **cmd_tbls, int n)
{
	int			i;
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = *cmd_tbls;
	if (cmd_tbl != NULL)
	{
		i = 0;
		while (i != n)
		{
			free_cmd_tbl(&cmd_tbl[i]);
			i++;
		}
	}
	free_if_not_null((void **)cmd_tbls);
}

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

void	clean_exit(t_shell *shell, int if_error)
{
	free_cmd_tbls(&shell->cmd_tbls, shell->n_cmd_tbls);
	delete_heredocs();
	free_tkn_tbl(&shell->tkn_tbl);
	free_if_not_null((void **)&shell->prompt);
	free_input(shell);
	if (shell->if_history_exists == TRUE)
		rl_clear_history();
	close(shell->std_in_out[0]);
	close(shell->std_in_out[1]);
	free(shell);
	exit (if_error);
}

void	exit_if_true(t_shell *shell, int if_true, int if_error)
{
	if (if_true == TRUE)
		clean_exit(shell, if_error);
}
