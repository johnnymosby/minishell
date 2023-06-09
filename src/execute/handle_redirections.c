/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:54:45 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 00:05:09 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	skip_n_pipes(t_tkn_tbl	*tkn_tbl, int n)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		if (j == n)
			return (i);
		if (tkn_tbl->tkns[i].type == FT_PIPE)
			j++;
		i++;
	}
	return (i);
}

static int	open_file(const char *pathname, t_type type, int n_cmd_tbl,
	t_shell *shell)
{
	int	fd;

	if (type == FT_LESS && access(pathname, R_OK) == -1)
		return (write_file_error_message(pathname), FALSE);
	if (type == FT_LESS)
		fd = open(pathname, O_RDONLY);
	else if (type == FT_DGREAT)
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == FT_GREAT)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd <= -1)
		return (write_file_error_message(pathname), FALSE);
	if (type == FT_LESS)
	{
		if (shell->cmd_tbls[n_cmd_tbl].in != -1)
			close(shell->cmd_tbls[n_cmd_tbl].in);
		shell->cmd_tbls[n_cmd_tbl].in = fd;
	}
	else if (type == FT_GREAT || type == FT_DGREAT)
	{
		if (shell->cmd_tbls[n_cmd_tbl].out != -1)
			close(shell->cmd_tbls[n_cmd_tbl].out);
		shell->cmd_tbls[n_cmd_tbl].out = fd;
	}
	return (TRUE);
}

static int	open_heredoc(t_cmd_tbl *cmd_tbls, int n_cmd_tbl, t_shell *shell)
{
	int		fd;
	char	*pathname;
	char	*file_id;

	file_id = ft_itoa(n_cmd_tbl);
	if (file_id == NULL)
		exit_if_true(shell, TRUE, FT_ERROR);
	pathname = ft_strjoin("/tmp/tmp_heredoc_", file_id);
	free(file_id);
	if (pathname == NULL)
		exit_if_true(shell, TRUE, FT_ERROR);
	if (access(pathname, R_OK) != 0)
		return (write_file_error_message(pathname), free(pathname), FALSE);
	fd = open(pathname, O_RDONLY);
	if (fd <= -1)
	{
		write_file_error_message(pathname);
		free(pathname);
		exit_if_true(shell, TRUE, FT_ERROR);
	}
	if (cmd_tbls[n_cmd_tbl].in != -1)
		close(cmd_tbls[n_cmd_tbl].in);
	cmd_tbls[n_cmd_tbl].in = fd;
	free(pathname);
	return (TRUE);
}

static int	open_redirection(t_tkn_tbl *tkn_tbl, int n_cmd_tbl,
	int i, t_shell *shell)
{
	int		if_no_error;
	t_type	type;
	char	*pathname;
	int		last_heredoc_id;

	if_no_error = TRUE;
	type = tkn_tbl->tkns[i].type;
	pathname = tkn_tbl->tkns[i + 1].cntnt;
	last_heredoc_id = find_last_heredoc_in_cmd(tkn_tbl, i);
	if ((type == FT_LESS || type == FT_GREAT || type == FT_DGREAT))
		if_no_error = open_file(pathname, type, n_cmd_tbl, shell);
	else if (type == FT_DLESS && i == last_heredoc_id)
		if_no_error = open_heredoc(shell->cmd_tbls, n_cmd_tbl, shell);
	if (if_no_error == FALSE)
		return (set_exit_code(shell, 1), FALSE);
	return (TRUE);
}

int	handle_redirections(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls, int n_cmd_tbl,
	t_shell *shell)
{
	int		i;
	t_type	type;

	i = skip_n_pipes(tkn_tbl, n_cmd_tbl);
	while (i != tkn_tbl->n_tkns)
	{
		type = tkn_tbl->tkns[i].type;
		if (type == FT_PIPE)
			return (TRUE);
		if (type == FT_LESS || type == FT_DLESS
			|| type == FT_GREAT || type == FT_DGREAT)
		{
			if (open_redirection(tkn_tbl, n_cmd_tbl, i, shell) == FALSE)
				return (FALSE);
			i += 2;
		}
		else
			i += 1;
	}
	return (TRUE);
}
