/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:40:40 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/26 19:11:33 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_zero(char *s)
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

static int	is_numeric_argument(char *s)
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

static int	exit_numeric_argument_required(t_shell *shell, t_cmd_tbl *cmd_tbl)
{
	if (shell->n_cmd_tbls == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd_tbl->args[0], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	if (shell->n_cmd_tbls == 1)
		clean_exit(shell, 2);
	return (FALSE);
}

static int	return_too_many_arguments(t_shell *shell)
{
	if (shell->n_cmd_tbls == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	shell->exit_code = 1;
	return (FALSE);
}

int	ft_exit(t_shell *shell, t_cmd_tbl *cmd_tbl)
{
	if (cmd_tbl->args == NULL && shell->n_cmd_tbls == 1)
		return (ft_putstr_fd("exit\n", STDERR_FILENO),
			clean_exit(shell, shell->exit_code), FALSE);
	if (cmd_tbl->args[1] == NULL)
	{
		if (is_numeric_argument(cmd_tbl->args[0]) == TRUE)
		{
			if (shell->n_cmd_tbls == 1)
			{
				ft_putstr_fd("exit\n", STDERR_FILENO);
				clean_exit(shell, ft_atoi(cmd_tbl->args[0]) % 256);
			}
			return (TRUE);
		}
		else
			return (exit_numeric_argument_required(shell, cmd_tbl));
	}
	if (is_numeric_argument(cmd_tbl->args[0]) == TRUE)
		return (return_too_many_arguments(shell));
	else
		return (exit_numeric_argument_required(shell, cmd_tbl));
}
