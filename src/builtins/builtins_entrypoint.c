/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_entrypoint.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:07:45 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 17:27:25 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

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
	else
		return (FT_OTHER);
}

int	execute_builtin(t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	if (what_command(cmd_tbl->cmd) == FT_CD)
		return (ft_cd(cmd_tbl, shell));
	else if (what_command(cmd_tbl->cmd) == FT_ECHO)
		return (ft_echo(cmd_tbl->args));
	else if (what_command(cmd_tbl->cmd) == FT_PWD)
		return (ft_pwd());
	else if (what_command(cmd_tbl->cmd) == FT_EXIT)
		return (ft_exit(shell, cmd_tbl));
	else if (what_command(cmd_tbl->cmd) == FT_ENV)
		return (ft_env(shell));
	else if (what_command(cmd_tbl->cmd) == FT_EXPORT)
		return (ft_export(shell, cmd_tbl->args));
	else
		return (FALSE);
}
