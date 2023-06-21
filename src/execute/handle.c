/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:48:14 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/21 11:04:35 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fd(int *fd)
{
	if (*fd >= 0)
		close(*fd);
}

void	handle_fd(int *fd)
{
	close_fd(fd);
	*fd = -1;
}

int	handle_infile(int i, int *prevpipe, t_shell *shell)
{
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	if (cmd_tbl->in >= 0)
		return (handle_fd(prevpipe), TRUE);
	else if (prevpipe >= 0)
	{
		cmd_tbl->in = *prevpipe;
		*prevpipe = -1;
		return (TRUE);
	}
	else
	{
		if (access("/dev/null", R_OK) == -1)
			return (write_file_error_message("/dev/null"), FALSE);
		cmd_tbl->in = open("/dev/null", O_RDONLY);
		if (cmd_tbl->in < 0)
			return (write_file_error_message("/dev/null"), FALSE);
	}
	return (TRUE);
}

int	handle_outfile(int *fd, int i, int *prevpipe, t_shell *shell)
{
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[i]);
	if (cmd_tbl->out >= 0)
		return (handle_fd(prevpipe), TRUE);
	else if (shell->cmd_tbls[i + 1].in_file != NULL)
	{
		handle_fd(prevpipe);
		if (access("/dev/null", W_OK) == -1)
			return (write_file_error_message("/dev/null"), FALSE);
		cmd_tbl->out = open("/dev/null", O_WRONLY);
		if (cmd_tbl->out < 0)
			return (write_file_error_message("/dev/null"), FALSE);
	}
	else
	{
		if (pipe(fd) == -1)
		{
			handle_fd(prevpipe);
			clean_exit(shell, FT_ERROR);
		}
		if (cmd_tbl->out < 0)
			cmd_tbl->out = fd[1];
	}
	return (TRUE);
}
