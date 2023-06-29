/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_last_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:35:42 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/29 17:30:42 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	wait_child_processes(t_shell *shell)
{
	int	status;

	while (wait(&status) > 0)
		;
	if (g_status == TRUE)
		shell->exit_code = 130;
	else
		shell->exit_code = status;
}

static int	execute_in_child(t_shell *shell, int i)
{
	pid_t		pid;
	t_cmd_tbl	*cmd_tbl;
	char		*pathname;

	cmd_tbl = &(shell->cmd_tbls[i]);
	pathname = construct_pathname(cmd_tbl->cmd, shell);
	if (pathname == NULL)
		return (FALSE);
	add_command_to_args(pathname, i, shell);
	pid = fork();
	if (pid < 0)
		print_error_and_exit(shell);
	else if (pid == 0)
	{
		check_signals_in_child(&(shell->termios));
		enable_redirections(shell->cmd_tbls, i);
		if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
			exit (1);
	}
	return (TRUE);
}

int	execute_last_cmd(t_shell *shell, int i, int prevpipe)
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
	if (handle_infile(i, &prevpipe, shell) == FALSE)
		return (set_exit_code(shell, 1), FALSE);
	if (what_command(cmd_tbl->cmd) != FT_OTHER)
	{
		enable_redirections(shell->cmd_tbls, i);
		shell->exit_code = execute_builtin(cmd_tbl, shell);
	}
	else if (execute_in_child(shell, i) == FALSE)
		return (FALSE);
	check_signals_in_parent(&(shell->termios));
	wait_child_processes(shell);
	if (cmd_tbl->in >= 0)
		close_fd(&prevpipe);
	close_files(cmd_tbl);
	return (TRUE);
}
