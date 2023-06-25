/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:07:34 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 16:29:07 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



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
		clean_exit(shell, FT_ERROR);
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
	if (what_command(shell->cmd_tbls[0].cmd) != FT_OTHER)
	{
		enable_redirections(shell->cmd_tbls, 0);
		shell->exit_code = execute_builtin(shell->cmd_tbls, shell);
		return ;
	}
	pathname = construct_pathname(shell->cmd_tbls[0].cmd, shell);
	if (pathname == NULL)
		return (write_file_error_message(shell->cmd_tbls[0].cmd));
	add_command_to_args(pathname, 0, shell);
	pid = fork();
	if (pid < 0)
		print_error_and_exit(shell);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		enable_redirections(shell->cmd_tbls, 0);
		if (execve(pathname, shell->cmd_tbls->args, shell->envs) < 0)
			exit (1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	if (g_status == CMD_SIG || g_status == NOCMD_SIG)
		shell->exit_code = 130;
	else
		shell->exit_code = status;
}

void	execute(t_shell *shell)
{
	g_status = CMD_NOSIG;
	if (shell->n_cmd_tbls <= 1)
		execute_without_pipes(shell);
	else
		execute_with_pipes(shell);
}
