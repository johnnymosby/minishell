/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd_tables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:06:15 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/19 14:48:46 by rbasyrov         ###   ########.fr       */
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

int	find_last_in_file_index(t_tkn_tbl *tkn_tbl, int i)
{
	int	ind;

	ind = -1;
	while (i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
			return (ind);
		if (tkn_tbl->tkns[i].type == FT_LESS
			|| tkn_tbl->tkns[i].type == FT_DLESS)
			ind = i;
		i++;
	}
	return (ind);
}

int	find_last_out_file_index(t_tkn_tbl *tkn_tbl, int i)
{
	int	ind;

	ind = -1;
	while (i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
			return (ind);
		if (tkn_tbl->tkns[i].type == FT_GREAT
			|| tkn_tbl->tkns[i].type == FT_DGREAT)
			ind = i;
		i++;
	}
	return (ind);
}

char	*make_tmp_heredoc_pathname(t_shell *shell, int j)
{
	char	*pathname;
	char	*file_id;

	file_id = ft_itoa(j);
	if (file_id == NULL)
		clean_exit(shell, TRUE);
	pathname = ft_strjoin("/tmp/tmp_heredoc_", file_id);
	free(file_id);
	if (pathname == NULL)
		clean_exit(shell, TRUE);
	return (pathname);
}

char	*find_last_in_file(t_shell *shell, t_tkn_tbl *tkn_tbl, int i, int j)
{
	char	*file;
	int		ind;

	file = NULL;
	ind = find_last_in_file_index(tkn_tbl, i);
	if (ind < 0)
		return (NULL);
	if (tkn_tbl->tkns[ind].type == FT_LESS)
		return (tkn_tbl->tkns[ind + 1].cntnt);
	else if (tkn_tbl->tkns[ind].type == FT_DLESS)
		return (make_tmp_heredoc_pathname(shell, j));
	else
		return (NULL);
}

char	*find_last_out_file(t_tkn_tbl *tkn_tbl, int i, int j)
{
	char	*file;
	int		ind;

	file = NULL;
	ind = find_last_out_file_index(tkn_tbl, i);
	if (ind < 0)
		return (NULL);
	else
		return (tkn_tbl->tkns[ind + 1].cntnt);
}

int	construct_cmd_table(t_tkn_tbl *tkn_tbl, t_shell *shell, int i, int j)
{
	t_cmd_tbl *cmd_tbl;

	(void) j;
	cmd_tbl = &(shell->cmd_tbls[j]);
	cmd_tbl->max_n_args = 4;
	cmd_tbl->in = -1;
	//cmd_tbl->in_file = find_last_in_file(shell, tkn_tbl, i, j);
	cmd_tbl->out = -1;
	//cmd_tbl->out_file = find_last_out_file(tkn_tbl, i, j);
	i = init_cmd_and_args(tkn_tbl, shell, i, j);
	return (i);
}

void	construct_cmd_tables(t_tkn_tbl *tkn_tbl, t_shell *shell)
{
	int	i;
	int	j;

	shell->n_cmd_tbls = count_pipes(tkn_tbl) + 1;
	shell->cmd_tbls = ft_calloc(shell->n_cmd_tbls, sizeof(t_cmd_tbl));
	if (shell->cmd_tbls == NULL)
		clean_exit(shell, FT_ERROR);
	i = 0;
	j = 0;
	while (i != tkn_tbl->n_tkns)
	{
		i = construct_cmd_table(tkn_tbl, shell, i, j);
		j++;
	}
}
