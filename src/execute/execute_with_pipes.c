/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:07:06 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/28 18:41:48 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	construct_pathname_safely(char **pathname, int i, t_cmd_tbl *cmd_tbl,
	t_shell *shell)
{
	*pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (*pathname == NULL)
		return (FALSE);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_fd(fd);
		enable_redirections(shell->cmd_tbls, i);
		if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
			exit (1);
	}
	handle_fd(fd + 1);
	*prevpipe = fd[0];
	return (TRUE);
}

static int	prepare_to_execution(int *prevpipe, int i, int *fd, t_shell *shell)
{
	t_cmd_tbl	*cmd_tbl;
	t_tkn_tbl	*tkn_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	tkn_tbl = shell->tkn_tbl;
	if (handle_redirections(tkn_tbl, shell->cmd_tbls,
			i, shell) == FALSE)
		return (handle_fd(prevpipe), FALSE);
	fd[0] = -1;
	fd[1] = -1;
	return (TRUE);
}

int	execute_cmd(int *prevpipe, int i, t_shell *shell)
{
	int			fd[2];
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	if (prepare_to_execution(prevpipe, i, fd, shell) == FALSE)
		return (FALSE);
	if (cmd_tbl->cmd == NULL)
		return (handle_fd(prevpipe), TRUE);
	handle_infile(i, prevpipe, shell);
	handle_outfile(fd, i, prevpipe, shell);
	if (what_command(cmd_tbl->cmd) != FT_OTHER)
	{
		enable_redirections(shell->cmd_tbls, i);
		shell->exit_code = execute_builtin(cmd_tbl, shell);
		if (fd[1] >= 0)
			close(fd[1]);
		dup2(shell->std_in_out[1], STDOUT_FILENO);
		*prevpipe = fd[0];
	}
	else if (execute_child_and_parent(fd, prevpipe, i, shell) == FALSE)
		return (set_exit_code(shell, 1), FALSE);
	handle_fd(fd + 1);
	return (TRUE);
}

void	execute_with_pipes(t_shell *shell)
{
	int	*prevpipe;
	int	prevpipe_val;
	int	i;

	prevpipe_val = 0;
	prevpipe = &prevpipe_val;
	i = 0;
	while (i != shell->n_cmd_tbls)
	{
		if (i == shell->n_cmd_tbls - 1)
		{
			g_status = CMD_NOSIG;
			execute_last_cmd(shell, i, *prevpipe);
			return ;
		}
		else
		{
			g_status = CMD_NOSIG;
			execute_cmd(prevpipe, i, shell);
		}
		i++;
	}
}
