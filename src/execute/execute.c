/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:07:34 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 15:09:45 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_redirections(t_cmd_tbl *cmd_tbl)
{
	if (cmd_tbl->in != -1)
	{
		close(cmd_tbl->in);
		cmd_tbl->in = -1;
	}
	if (cmd_tbl->out != -1)
	{
		close(cmd_tbl->in);
		cmd_tbl->out = -1;
	}
}

int	open_file(const char *pathname, t_type type, int n_cmd_tbl, t_shell *shell)
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
		return (write_file_error_message(pathname), clean_exit(shell, TRUE), 0);
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

int	open_heredoc(t_cmd_tbl *cmd_tbls, int n_cmd_tbl, t_shell *shell)
{
	int		fd;
	char	*pathname;
	char	*file_id;

	file_id = ft_itoa(n_cmd_tbl);
	if (file_id == NULL)
		clean_exit(shell, TRUE);
	pathname = ft_strjoin("/tmp/tmp_heredoc_", file_id);
	free(file_id);
	if (pathname == NULL)
		clean_exit(shell, TRUE);
	if (access(pathname, R_OK) != 0)
		return (write_file_error_message(pathname), free(pathname), FALSE);
	fd = open(pathname, O_RDONLY);
	if (fd <= -1)
	{
		write_file_error_message(pathname);
		free(pathname);
		clean_exit(shell, TRUE);
	}
	if (cmd_tbls[n_cmd_tbl].in != -1)
		close(cmd_tbls[n_cmd_tbl].in);
	cmd_tbls[n_cmd_tbl].in = fd;
	free(pathname);
	return (TRUE);
}

int	open_redirection(t_tkn_tbl *tkn_tbl, int n_cmd_tbl,
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
		return (FALSE);
	return (TRUE);
}

int	skip_n_pipes(t_tkn_tbl	*tkn_tbl, int n)
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

int	handle_redirections(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls, int n_cmd_tbl, t_shell *shell)
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

void	add_command_to_args(char *pathname, int i, t_shell *shell)
{
	char		**new_argv;
	t_cmd_tbl	*cmd_tbl;
	int			n;

	cmd_tbl = &(shell->cmd_tbls[i]);
	cmd_tbl->n_args += 1;
	new_argv = ft_calloc(cmd_tbl->n_args + 1, sizeof(char *));
	if (new_argv == NULL)
	{
		free(new_argv);
		clean_exit(shell, TRUE);
	}
	new_argv[0] = pathname;
	n = 1;
	while (n < cmd_tbl->n_args)
	{
		new_argv[n] = cmd_tbl->args[n - 1];
		n++;
	}
	free(cmd_tbl->args);
	cmd_tbl->args = new_argv;
}

void	enable_redirections(t_cmd_tbl *cmd_tbls, int i)
{
	if (cmd_tbls[i].in != -1)
		dup2(cmd_tbls[i].in, STDIN_FILENO);
	if (cmd_tbls[i].out != -1)
		dup2(cmd_tbls[i].out, STDOUT_FILENO);
}

void	execute_without_pipes(t_shell *shell)
{
	pid_t	pid;
	char	*pathname;
	int		status;

	if (handle_redirections(shell->tkn_tbl, shell->cmd_tbls, 0, shell)
		== FALSE)
		return ;
	if (shell->cmd_tbls[0].cmd == NULL)
		return ;
	pathname = construct_pathname(shell->cmd_tbls[0].cmd, shell);
	if (pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[0].cmd));
	add_command_to_args(pathname, 0, shell);
	pid = fork();
	if (pid < 0)
		print_error_and_exit(shell);
	else if (pid == 0)
	{
		enable_redirections(shell->cmd_tbls, 0);
		if (execve(pathname, shell->cmd_tbls->args, shell->envs) < 0)
			exit (1);
	}
	else
		waitpid(pid, &status, 0);
}

void	execute(t_shell *shell)
{
	if (shell->n_cmd_tbls <= 1)
		execute_without_pipes(shell);
	else
		execute_with_pipes(shell);
}
