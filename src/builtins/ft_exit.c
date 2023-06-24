/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:40:40 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/24 02:10:27 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_zero(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-')
		i++;
	while (s[i] != '\0' && s[i] == '0')
		i++;
	if (s[i] != '\0')
		return (FALSE);
	else
		return (TRUE);
}

int	is_numeric_argument(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i] != '\0' && ('0' <= s[i] && s[i] <= '9'))
		i++;
	if (s[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

//i think  exit code should be a global variable coming from signals etc.
int	ft_exit(t_shell *shell, t_cmd_tbl *cmd_tbl)
{
	int	arg;

	if (cmd_tbl->args == NULL)
	{
		if (shell->n_cmd_tbls == 1)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			clean_exit(shell, shell->exit_code);
		}
		return (TRUE);
	}
	if (cmd_tbl->args[1] == NULL)
	{
		if (is_numeric_argument(cmd_tbl->args[0]) == TRUE)
		{
			arg = ft_atoi(cmd_tbl->args[0]) % 256;
			if (shell->n_cmd_tbls == 1)
			{
				ft_putstr_fd("exit\n", STDERR_FILENO);
				clean_exit(shell, arg);
			}
			return (TRUE);
		}
		else
		{
			if (shell->n_cmd_tbls == 1)
				ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd_tbl->args[0], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			if (shell->n_cmd_tbls == 1)
				clean_exit(shell, 255);
			return (FALSE);
		}
	}
	if (is_numeric_argument(cmd_tbl->args[0]) == TRUE)
	{
		if (shell->n_cmd_tbls == 1)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_code = 255;
		return (FALSE);
	}
	else
	{
		if (shell->n_cmd_tbls == 1)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd_tbl->args[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		if (shell->n_cmd_tbls == 1)
			clean_exit(shell, 255);
		return (FALSE);
	}
}
