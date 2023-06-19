/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:07:06 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/19 15:23:22 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_redirections_pipes(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls, int n_cmd_tbl, t_shell *shell)
{
	int		i;
	t_type	type;

	i = 0;
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

int	execute_last_command(t_shell *shell, int i, int prevpipe)
{
	t_cmd_tbl	*cmd_tbl;
	t_tkn_tbl	*tkn_tbl;
	int			j;
	char		*pathname;
	pid_t		pid;
	int			status;

	cmd_tbl = &(shell->cmd_tbls[i]);
	tkn_tbl = shell->tkn_tbl;
	j = skip_n_pipes(tkn_tbl, i);
	if (handle_redirections_pipes(tkn_tbl, shell->cmd_tbls, j, shell) == FALSE)
	{
		if (prevpipe >= 0)
			close(prevpipe);
		return (FALSE);
	}
	if (cmd_tbl->cmd == NULL)
	{
		if (prevpipe >= 0)
			close(prevpipe);
		return (TRUE);
	}
	if (cmd_tbl->in < 0)
	{
		if (prevpipe >= 0)
			cmd_tbl->in = prevpipe;
		else
		{
			if (access("/dev/null", R_OK) == -1)
				return (write_file_error_message("/dev/null"), FALSE);
			cmd_tbl->in = open("/dev/null", O_RDONLY);
			if (cmd_tbl->in < 0)
				return (write_file_error_message("/dev/null"), FALSE);
		}
	}
	pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[i].cmd), FALSE);
	add_command_to_args(pathname, i, shell);
	pid = fork();
	if (pid < 0)
		print_error_and_exit(shell);
	else if (pid == 0)
	{
		enable_redirections(cmd_tbl, i);
		if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
			exit (1);
	}
	else
	{
		if (cmd_tbl->in >= 0)
			close(prevpipe);
		close_files(cmd_tbl);
		waitpid(pid, &status, 0);
	}
	return (TRUE);
}

int	execute_command(t_shell *shell, int i, int prevpipe)
{
	t_cmd_tbl	*cmd_tbl;
	t_tkn_tbl	*tkn_tbl;
	int			j;
	char		*pathname;
	pid_t		pid;
	int			status;
	int			fd[2];

	cmd_tbl = &(shell->cmd_tbls[i]);
	tkn_tbl = shell->tkn_tbl;
	j = skip_n_pipes(tkn_tbl, i);
	if (handle_redirections_pipes(tkn_tbl, shell->cmd_tbls, j, shell) == FALSE)
	{
		if (prevpipe >= 0)
			close(prevpipe);
		return (FALSE);
	}
	if (cmd_tbl->cmd == NULL)
	{
		if (prevpipe >= 0)
			close(prevpipe);
		return (TRUE);
	}
	if (cmd_tbl->in < 0)
	{
		if (prevpipe >= 0)
			cmd_tbl->in = prevpipe;
		else
		{
			if (access("/dev/null", R_OK) == -1)
				return (write_file_error_message("/dev/null"), FALSE);
			cmd_tbl->in = open("/dev/null", O_RDONLY);
			if (cmd_tbl->in < 0)
				return (write_file_error_message("/dev/null"), FALSE);
		}
	}
	pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[i].cmd), FALSE);
	add_command_to_args(pathname, i, shell);
	if (pipe(fd) == -1)
	{
		if (prevpipe >= 0)
			close(prevpipe);
		clean_exit(shell, TRUE);
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		print_error_and_exit(shell);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		if (cmd_tbl->out < 0)
			cmd_tbl->out = fd[1];
		enable_redirections(cmd_tbl, i);
		if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
			exit (1);
	}
	else
	{
		close(fd[1]);
		if (cmd_tbl->in >= 0)
			close(prevpipe);
		prevpipe = fd[0];
		close_files(cmd_tbl);
		waitpid(pid, &status, 0);
	}
	return (TRUE);
}

void	execute_with_pipes(t_shell *shell)
{
	int	prevpipe;
	int	i;

	prevpipe = STDIN_FILENO;
	i = 0;
	while (i != shell->n_cmd_tbls)
	{
		if (i == shell->n_cmd_tbls - 1)
		{
			execute_last_command(shell, i, prevpipe);
			return ;
		}
		else
		{
			prevpipe = execute_command(shell, i, prevpipe);
			if (prevpipe == -2)
				return ;
		}
		i++;
	}
}
