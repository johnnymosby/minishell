/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_entrypoint.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:07:45 by maruzibo          #+#    #+#             */
/*   Updated: 2023/07/02 11:56:31 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	what_command(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	if (i == 2 && !ft_strncmp(cmd, "cd", i))
		return (FT_CD);
	else if (i == 4 && !ft_strncmp(cmd, "echo", i))
		return (FT_ECHO);
	else if (i == 3 && !ft_strncmp(cmd, "pwd", i))
		return (FT_PWD);
	else if (i == 4 && !ft_strncmp(cmd, "exit", i))
		return (FT_EXIT);
	else if (i == 3 && !ft_strncmp(cmd, "env", i))
		return (FT_ENV);
	else if (i == 6 && !ft_strncmp(cmd, "export", i))
		return (FT_EXPORT);
	else if (i == 5 && !ft_strncmp(cmd, "unset", i))
		return (FT_UNSET);
	else
		return (FT_OTHER);
}

static int	is_not_executable_in_pipe(char *cmd, t_shell *shell)
{
	if (shell->n_cmd_tbls > 1
		&& (what_command(cmd) == FT_CD
			|| what_command(cmd) == FT_EXIT
			|| what_command(cmd) == FT_EXPORT
			|| what_command(cmd) == FT_UNSET))
		return (TRUE);
	else
		return (FALSE);
}

int	execute_builtin(t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (shell->n_cmd_tbls > 1
		&& is_not_executable_in_pipe(cmd_tbl->cmd, shell) == TRUE)
		return (0);
	if (what_command(cmd_tbl->cmd) == FT_CD)
		return (ft_cd(cmd_tbl, shell));
	else if (what_command(cmd_tbl->cmd) == FT_ECHO)
		return (ft_echo(cmd_tbl->args));
	else if (what_command(cmd_tbl->cmd) == FT_PWD)
		return (ft_pwd(shell));
	else if (what_command(cmd_tbl->cmd) == FT_EXIT)
		return (ft_exit(shell, cmd_tbl));
	else if (what_command(cmd_tbl->cmd) == FT_ENV)
		return (ft_env(shell, cmd_tbl->args));
	else if (what_command(cmd_tbl->cmd) == FT_EXPORT)
		return (ft_export(shell, cmd_tbl->args));
	else if (what_command(cmd_tbl->cmd) == FT_UNSET)
		return (ft_unset(shell, cmd_tbl->args));
	else
		return (FALSE);
}
