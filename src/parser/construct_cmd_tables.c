/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd_tables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:06:15 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/09 15:31:46 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_pipes(t_tkn_tbl *tkn_tbl)
{
	int	n_pipes;
	int	i;

	n_pipes = 0;
	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
			n_pipes++;
		i++;
	}
	return (n_pipes);
}

void	increase_args_array(char ***args, t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	int			old_max;
	char		**new_args_array;
	int			i;
	char		**arr;

	arr = *args;
	old_max = cmd_tbl->max_n_args;
	cmd_tbl->max_n_args = (int)(1.5 * old_max);
	new_args_array = ft_calloc(cmd_tbl->max_n_args, sizeof(char *));
	if (new_args_array == NULL)
		clean_exit(shell, FT_ERROR);
	i = 0;
	while (i != old_max)
	{
		new_args_array[i] = arr[i];
		i++;
	}
	free_if_not_null((void **)args);
	*args = new_args_array;
}

void	add_arg(char *arg, t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	if (cmd_tbl->args == NULL)
	{
		cmd_tbl->args = ft_calloc(cmd_tbl->max_n_args + 1, sizeof (char *));
		if (cmd_tbl->args == NULL)
			clean_exit(shell, FT_ERROR);
	}
	if (cmd_tbl->n_args == cmd_tbl->max_n_args)
		increase_args_array(&(cmd_tbl->args), cmd_tbl, shell);
	cmd_tbl->args[cmd_tbl->n_args] = ft_strdup(arg);
	if (cmd_tbl->args[cmd_tbl->n_args] == NULL)
		clean_exit(shell, FT_ERROR);
	cmd_tbl->n_args += 1;
}

int	init_cmd_and_args(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbl,
	t_shell *shell, int i)
{
	while (i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
		{
			i++;
			return (i);
		}
		if (tkn_tbl->tkns[i].type == FT_WORD && cmd_tbl->cmd == NULL)
		{
			cmd_tbl->cmd = ft_strdup(tkn_tbl->tkns[i].cntnt);
			if (cmd_tbl->cmd == NULL)
				clean_exit(shell, FT_ERROR);
		}
		else if (tkn_tbl->tkns[i].type == FT_WORD)
		{
			add_arg(tkn_tbl->tkns[i].cntnt, cmd_tbl, shell);
		}
		i++;
	}
	return (i);
}

int	construct_cmd_table(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbl,
	t_shell *shell, int i)
{
	i = init_cmd_and_args(tkn_tbl, cmd_tbl, shell, i);
	return (i);
}

void	construct_cmd_tables(t_tkn_tbl *tkn_tbl, t_shell *shell)
{
	int	i;
	int	j;

	shell->n_cmd_tbls = count_pipes(tkn_tbl) + 1;
	shell->cmd_tbls = ft_calloc(shell->n_cmd_tbls, sizeof(t_cmd_tbl));
	shell->cmd_tbls->max_n_args = 4;
	if (shell->cmd_tbls == NULL)
		clean_exit(shell, FT_ERROR);
	i = 0;
	j = 0;
	while (i != tkn_tbl->n_tkns)
	{
		i = construct_cmd_table(tkn_tbl, &(shell->cmd_tbls[j]), shell, i);
		j++;
	}
}
