/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_and_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:20:58 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 17:22:21 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	increase_args_array(char ***args, t_cmd_tbl *cmd_tbl,
	t_shell *shell)
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

static void	add_arg(char *arg, t_cmd_tbl *cmd_tbl, t_shell *shell)
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

int	init_cmd_and_args(t_tkn_tbl *tkn_tbl, t_shell *shell, int i, int j)
{
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[j]);
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
		else
			i++;
		i++;
	}
	return (i);
}
