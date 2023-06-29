/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:16:18 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/29 17:11:51 by rbasyrov         ###   ########.fr       */
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

void	finalise_exit_code(t_shell *shell, int status)
{
	if (g_status == TRUE)
		shell->exit_code = 130;
	else
	{
		if (status == 0)
			shell->exit_code = status;
		else if (status % 256 == 0)
			shell->exit_code = status / 256;
		else
			shell->exit_code = status % 256;
	}
}
