/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:07:06 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 15:14:15 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fd(int *fd)
{
	if (*fd >= 0)
		close(*fd);
}

void	handle_fd(int *fd)
{
	close_fd(fd);
	*fd = -1;
}

int	handle_infile(int i, int *prevpipe, t_shell *shell)
{
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	if (cmd_tbl->in >= 0)
		return (handle_fd(prevpipe), TRUE);
	else if (prevpipe >= 0)
	{
		cmd_tbl->in = *prevpipe;
		*prevpipe = -1;
		return (TRUE);
	}
	else
	{
		if (access("/dev/null", R_OK) == -1)
			return (write_file_error_message("/dev/null"), FALSE);
		cmd_tbl->in = open("/dev/null", O_RDONLY);
		if (cmd_tbl->in < 0)
			return (write_file_error_message("/dev/null"), FALSE);
	}
	return (TRUE);
}

int	handle_outfile(int *fd, int i, int *prevpipe, t_shell *shell)
{
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	if (cmd_tbl->out >= 0)
		return (handle_fd(prevpipe), TRUE);
	else if (shell->cmd_tbls[i + 1].in_file != NULL)
	{
		handle_fd(prevpipe);
		if (access("/dev/null", W_OK) == -1)
			return (write_file_error_message("/dev/null"), FALSE);
		cmd_tbl->out = open("/dev/null", O_WRONLY);
		if (cmd_tbl->out < 0)
			return (write_file_error_message("/dev/null"), FALSE);
		return (TRUE);
	}
	else
	{
		if (pipe(fd) == -1)
		{
			handle_fd(prevpipe);
			clean_exit(shell, TRUE);
		}
		if (cmd_tbl->out < 0)
			cmd_tbl->out = fd[1];
	}
	return (TRUE);
}

int	construct_pathname_safely(char **pathname, int i, t_cmd_tbl *cmd_tbl,
	t_shell *shell)
{
	*pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (*pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[i].cmd), FALSE);
	add_command_to_args(*pathname, i, shell);
	return (TRUE);
}

int	execute_child_and_parent(int *fd, int *prevpipe, int i, t_shell *shell)
{
	pid_t		pid;
	char		*pathname;
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	if (construct_pathname_safely(&pathname, i, cmd_tbl, shell) == FALSE)
		return (FALSE);
	pid = fork();
	if (pid < 0)
		print_error_and_exit(shell);
	else if (pid == 0)
	{
		handle_fd(fd);
		enable_redirections(shell->cmd_tbls, i);
		if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
			exit (1);
	}
	handle_fd(fd + 1);
	*prevpipe = fd[0];
	return (TRUE);
}

int	execute_cmd(int *prevpipe, int i, t_shell *shell)
{
	t_tkn_tbl	*tkn_tbl;
	int			fd[2];
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	tkn_tbl = shell->tkn_tbl;
	if (handle_redirections(tkn_tbl, shell->cmd_tbls,
			i, shell) == FALSE)
		return (close_fd(prevpipe), FALSE);
	if (cmd_tbl->cmd == NULL)
		return (close_fd(prevpipe), TRUE);
	fd[0] = -1;
	fd[1] = -1;
	if (handle_infile(i, prevpipe, shell) == FALSE)
		return (FALSE);
	if (handle_outfile(fd, i, prevpipe, shell) == FALSE)
		return (FALSE);
	if (execute_child_and_parent(fd, prevpipe, i, shell) == FALSE)
		return (FALSE);
}

int	populate_infile(t_cmd_tbl *cmd_tbl, int prevpipe)
{
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
	return (TRUE);
}

void	wait_child_processes(void)
{
	int	status;

	while (wait(&status) > 0)
		;
}

void	execute_in_child(t_shell *shell, char *pathname, t_cmd_tbl *cmd_tbl, int i)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		print_error_and_exit(shell);
	else if (pid == 0)
	{
		enable_redirections(shell->cmd_tbls, i);
		if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
			exit (1);
	}
}

int	execute_last_command(t_shell *shell, int i, int prevpipe)
{
	t_cmd_tbl	*cmd_tbl;
	t_tkn_tbl	*tkn_tbl;
	char		*pathname;

	cmd_tbl = &(shell->cmd_tbls[i]);
	tkn_tbl = shell->tkn_tbl;
	if (handle_redirections(tkn_tbl, shell->cmd_tbls, i, shell) == FALSE)
		return (close_fd(&prevpipe), FALSE);
	if (cmd_tbl->cmd == NULL)
		return (close_fd(&prevpipe), TRUE);
	if (populate_infile(cmd_tbl, prevpipe) == FALSE)
		return (FALSE);
	pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[i].cmd), FALSE);
	add_command_to_args(pathname, i, shell);
	execute_in_child(shell, pathname, cmd_tbl, i);
	wait_child_processes();
	if (cmd_tbl->in >= 0)
		close_fd(&prevpipe);
	close_files(cmd_tbl);
	return (TRUE);
}

void	execute_with_pipes(t_shell *shell)
{
	int	*prevpipe;
	int	prevpipe_val;
	int	i;

	prevpipe_val = STDIN_FILENO;
	prevpipe = &prevpipe_val;
	i = 0;
	while (i != shell->n_cmd_tbls)
	{
		if (i == shell->n_cmd_tbls - 1)
		{
			execute_last_command(shell, i, *prevpipe);
			return ;
		}
		else
		{
			if (execute_cmd(prevpipe, i, shell) == FALSE)
				return ;
		}
		i++;
	}
}
