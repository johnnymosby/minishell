/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_without_pipes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:17:09 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/27 14:32:08 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	prepare_to_execution(t_shell *shell)
{
	if (handle_redirections(shell->tkn_tbl, shell->cmd_tbls, 0, shell)
		== FALSE)
		return (FALSE);
	if (shell->cmd_tbls[0].cmd == NULL)
		return (FALSE);
	if (what_command(shell->cmd_tbls[0].cmd) != FT_OTHER)
	{
		enable_redirections(shell->cmd_tbls, 0);
		shell->exit_code = execute_builtin(shell->cmd_tbls, shell);
		return (FALSE);
	}
	return (TRUE);
}

void	execute_without_pipes(t_shell *shell)
{
	pid_t	pid;
	char	*pathname;
	int		status;

	if (prepare_to_execution(shell) == FALSE)
		return ;
	pathname = construct_pathname(shell->cmd_tbls[0].cmd, shell);
	if (pathname == NULL)
		return ;
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
		waitpid(pid, &status, 0);
	finalise_exit_code(shell, status);
}
