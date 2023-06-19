/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:07:06 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/19 23:47:56 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	handle_redirections_pipes(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls, int n_cmd_tbl, t_shell *shell)
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

void	close_prevpipe(int *prevpipe)
{
	if (*prevpipe >= 0)
		close(*prevpipe);
}

void	wait_child_processes(void)
{
	int	status;

	while (wait(&status) > 0)
		;
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
	int			j;
	char		*pathname;

	cmd_tbl = &(shell->cmd_tbls[i]);
	tkn_tbl = shell->tkn_tbl;
	j = skip_n_pipes(tkn_tbl, i);
	if (handle_redirections_pipes(tkn_tbl, shell->cmd_tbls, j, shell) == FALSE)
		return (close_prevpipe(&prevpipe), FALSE);
	if (cmd_tbl->cmd == NULL)
		return (close_prevpipe(&prevpipe), TRUE);
	if (populate_infile(cmd_tbl, prevpipe) == FALSE)
		return (FALSE);
	pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[i].cmd), FALSE);
	add_command_to_args(pathname, i, shell);
	execute_in_child(shell, pathname, cmd_tbl, i);
	wait_child_processes();
	if (cmd_tbl->in >= 0)
		close_prevpipe(&prevpipe);
	close_files(cmd_tbl);
	return (TRUE);
}
void	handle_prevpipe(int *prevpipe)
{
	close_prevpipe(prevpipe);
	*prevpipe = -1;
}

int	execute_command(t_shell *shell, int i, int *prevpipe)
{
	t_cmd_tbl	*cmd_tbl;
	t_tkn_tbl	*tkn_tbl;
	int			j;
	char		*pathname;
	pid_t		pid;
	int			fd[2];

	cmd_tbl = &(shell->cmd_tbls[i]);
	tkn_tbl = shell->tkn_tbl;
	j = skip_n_pipes(tkn_tbl, i);
	if (handle_redirections_pipes(tkn_tbl, shell->cmd_tbls, j, shell) == FALSE)
		return (handle_prevpipe(prevpipe), FALSE);
	if (cmd_tbl->cmd == NULL)
		return (handle_prevpipe(prevpipe), TRUE);
	pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[i].cmd), FALSE);
	add_command_to_args(pathname, i, shell);
	if (cmd_tbl->in < 0)
	{
		if (*prevpipe >= 0)
			cmd_tbl->in = *prevpipe;
		else
		{
			if (access("/dev/null", R_OK) == -1)
				return (write_file_error_message("/dev/null"), FALSE);
			cmd_tbl->in = open("/dev/null", O_RDONLY);
			if (cmd_tbl->in < 0)
				return (write_file_error_message("/dev/null"), FALSE);
		}
	}
	if (cmd_tbl->out < 0 && shell->cmd_tbls[i + 1].in_file == NULL)
	{
		if (pipe(fd) == -1)
		{
			handle_prevpipe(prevpipe);
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
			enable_redirections(shell->cmd_tbls, i);
			if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
				exit (1);
		}
		close(fd[1]);
		if (cmd_tbl->in >= 0)
			handle_prevpipe(prevpipe);
		*prevpipe = fd[0];
	}
	else if (cmd_tbl->out >= 0)
	{
		execute_in_child(shell, pathname, cmd_tbl, i);
		if (cmd_tbl->in >= 0)
			close(*prevpipe);
		*prevpipe = -1;
	}
	else if (shell->cmd_tbls[i + 1].in_file != NULL)
	{
		if (*prevpipe >= 0)
			close(*prevpipe);
		*prevpipe = -1;
		pid = fork();
		if (pid < 0)
			print_error_and_exit(shell);
		else if (pid == 0)
		{
			if (access("/dev/null", R_OK) == -1)
				return (write_file_error_message("/dev/null"), FALSE);
			cmd_tbl->out = open("/dev/null", O_RDONLY);
			if (cmd_tbl->out < 0)
				return (write_file_error_message("/dev/null"), FALSE);
			enable_redirections(shell->cmd_tbls, i);
			if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
				exit (1);
		}
		if (cmd_tbl->in >= 0 && *prevpipe >= 0)
			close(*prevpipe);
		*prevpipe = -1;
	}
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
			if (execute_command(shell, i, prevpipe) == FALSE)
				return ;
		}
		i++;
	}
}
