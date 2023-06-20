/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bults_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:07:45 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 17:41:20 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h" //"../inc/minishell.h"

extern int	signal;

int	ft_is_built(t_shell *shell)
{
	int		i;
	char	*cmd;

	cmd = shell->t_cmd_tbl[0];
	i = ft_strlen(cmd);
	if (i == 0)
		return (0);
	else if (i == 2 && !ft_strncmp(cmd, "cd", i))
		return (1);
	else if (i == 3 && !ft_strncmp(cmd, "env", i))
		return (1);
	else if (i == 3 && !ft_strncmp(cmd, "pwd", i))
		return (1);
	else if (i == 4 && !ft_strncmp(cmd, "echo", i))
		return (1);
	else if (i == 4 && !ft_strncmp(cmd, "exit", i))
		return (1);
       	else if (i == 5 && !ft_strncmp(cmd, "unset", i)) 
		return (1);
	else if (i == 6 && !ft_strncmp(cmd, "export", i))
		return (1);
	return (0);
}

int	builtin(t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd;

	j = 0;
	i = 0;
	while (j < n_cmd_tbls)
	{
		cmd = shell->t_cmd_tbl[0];
		i = ft_strlen(cmd);
		if (i == 2 && !ft_strncmp(cmd, "cd", i))
			signal = ft_cd(shell);
		else if (i == 3 && !ft_strncmp(cmd, "pwd", i))
			signal = ft_pwd(shell);
		else if (i == 4 && !ft_strncmp(cmd, "echo", i))
			signal = ft_echo(shell);
		else if (i == 4 && !ft_strncmp(cmd, "exit", i))
			signal = ft_exit(shell);
		else if (i == 5 && !ft_strncmp(cmd, "unset", i))
			signal = ft_unset(shell);
		else if (i == 6 && !ft_strncmp(cmd, "export", i))
			signal = ft_export(shell);
	}
	return (signal);
}
/*
int	main(int argc, char **argv)
{
	t_shell *shell;


}*/
