/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_entrypoint.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:07:45 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/23 23:55:31 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

t_cmd	what_command(char *cmd)
{
	int		i;

	i = ft_strlen(cmd);
	if (i == 2 && !ft_strncmp(cmd, "cd", i))
		return (FT_CD);
	else if (i == 4 && !ft_strncmp(cmd, "echo", i))
		return (FT_ECHO);
	else
		return (FT_OTHER);
}

int	execute_builtin(t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	if (what_command(cmd_tbl->cmd) == FT_CD)
		return (ft_cd(cmd_tbl, shell));
	else if (what_command(cmd_tbl->cmd) == FT_ECHO)
		return (ft_echo(cmd_tbl->args));
	else
		return (FALSE);
}
