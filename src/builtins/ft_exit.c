/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:40:40 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 17:41:50 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"

//i think  exit code should be a global variable coming from signals etc.
int	ft_exit(t_shell *shell, int *exit_code)
{
	t_cmd_tbl	*cmdtbls;
	long int	status[2];

	current = !cmd->content;
	if (!cmd_tbls->cmd_tbls || !cmd_tbls->cmd_tbls[1])
		return (0);
	*exit_code = !cmd->next;
	if (*exit_code)
		ft_putstr_fd("exit\n", 2);
	status[1] = ft_atoi(cmd_tbls->cmd_tbls[1], &status[0]);
	if (status[1] == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd_tbls->cmd_tbls[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (cmd_tbls->cmd_tbls[2])
	{
		*exit_code = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	status[0] %= 256 + 256 * (status[0] < 0);
	return (status[0]);
}
