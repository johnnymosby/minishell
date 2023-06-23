/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_tbl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:59:35 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/23 13:59:08 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_str_array(char ***args, int n_args)
{
	char	**arr;
	int		i;

	arr = *args;
	i = 0;
	while (i != n_args)
	{
		if (arr[i] != NULL)
		{
			free(arr[i]);
		}
		i++;
	}
	free_if_not_null((void **)args);
}

void	close_files(t_cmd_tbl *cmd_tbl)
{
	if (cmd_tbl->in >= 0)
	{
		close(cmd_tbl->in);
		cmd_tbl->in = -1;
	}
	if (cmd_tbl->out >= 0)
	{
		close(cmd_tbl->out);
		cmd_tbl->out = -1;
	}
}

void	free_cmd_tbl(t_cmd_tbl *cmd_tbl)
{
	int		i;

	i = 0;
	if (cmd_tbl->cmd != NULL)
		free(cmd_tbl->cmd);
	if (cmd_tbl->args != NULL)
		free_str_array(&cmd_tbl->args, cmd_tbl->n_args);
	close_files(cmd_tbl);
}
