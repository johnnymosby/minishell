/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:15:41 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 18:28:29 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"
//#include "../inc/minishell.h"

extern int	g_status;

int	ft_built(t_shell *shell)
{
	t_cmd_tbl	*cmd;
	int			n[2];

	n[0] = -1;
	n[1] = 0;
	while (++n[0] < shell->n_cmd_args)
	{
		cmd = shell->cmd_tbls;
		if (cmd->cmd)
			n[1] = ft_strlen(*cmd->cmd);
		if (cmd->cmd && n[1] == 4 && !ft_strncmp(*cmd->cmd, "exit", n[1]))
			g_status = ft_exit(shell);
		else if (n[0] == shell->n_cmd_args
			&& n[1] == 2 && a && !ft_strncmp(*cmd->cmd, "cd", n[1]))
			g_status = ft_cd(shell);
		else if (!cmd->next && n[1] == 6
			&& !ft_strncmp(*cmd->cmd, "export", n[1]))
			g_status = ft_export(shell);
		else if (!cmd->next && n[1] == 5
			&& !ft_strncmp(*cmd->cmd, "unset", n[1]))
			g_status = ft_unset(shell);
	}
	return (g_status);
}
