/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd_tables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:06:15 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/05 14:58:29 by rbasyrov         ###   ########.fr       */
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

void	add_arg(char **args, char *arg, t_cmd_tbl *cmd_tbl, t_shell *shell)
{
	int	i;

	i = 0;
	if (args == NULL)
	{
		args = ft_calloc(cmd_tbl->max_n_args + 1, sizeof (char *));
		if (args == NULL)
			clean_exit(shell, FT_ERROR);
	}
	if (cmd_tbl->n_args == cmd_tbl->max_n_args)
		increase_args_array(&args, cmd_tbl, shell);
	while (cmd_tbl->args[i] != NULL)
		i++;
	cmd_tbl->args[i] = ft_strdup(arg);
	if (cmd_tbl->args[i] == NULL)
		clean_exit(shell, FT_ERROR);
	cmd_tbl->n_args += 1;
}

void	init_cmd_and_args(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbl,
	t_shell *shell, int i)
{
	while (i != tkn_tbl->n_tkns && tkn_tbl->tkns[i].type != FT_PIPE)
	{
		if (tkn_tbl->tkns[i].type == FT_WORD && shell->cmd_tbls[i].cmd == NULL)
		{
			shell->cmd_tbls[i].cmd = ft_strdup(tkn_tbl->tkns[i].cntnt);
			if (tkn_tbl->tkns[i].cntnt == NULL)
				clean_exit(shell, FT_ERROR);
		}
		else if (tkn_tbl->tkns[i].type == FT_WORD)
		{
			add_arg(cmd_tbl->args, tkn_tbl->tkns[i].cntnt, cmd_tbl, shell);
		}
	}
}

int	construct_cmd_table(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbl,
	t_shell *shell, int i)
{
	init_cmd_and_args(tkn_tbl, cmd_tbl, shell, i);
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
		shell->cmd_tbls->n_args += 1;
		j++;
	}
}
