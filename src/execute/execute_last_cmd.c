/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_last_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:35:42 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 13:36:07 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



static void	wait_child_processes(t_shell *shell)
{
	int	status;

	while (wait(&status) > 0)
		;
	if (g_status == CMD_SIG)
		shell->exit_code = 130;
	else
		shell->exit_code = status;
}

static void	execute_in_child(t_shell *shell, char *pathname, t_cmd_tbl *cmd_tbl,
	int i)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		print_error_and_exit(shell);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		enable_redirections(shell->cmd_tbls, i);
		if (execve(pathname, cmd_tbl->args, shell->envs) < 0)
			exit (1);
	}
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
	else
	{
		pathname = construct_pathname(cmd_tbl->cmd, shell);
		if (pathname == NULL)
			return (write_file_error_message(shell->cmd_tbls[i].cmd), FALSE);
		add_command_to_args(pathname, i, shell);
		execute_in_child(shell, pathname, cmd_tbl, i);
	}
	wait_child_processes(shell);
	if (cmd_tbl->in >= 0)
		close_fd(&prevpipe);
	close_files(cmd_tbl);
	return (TRUE);
}
