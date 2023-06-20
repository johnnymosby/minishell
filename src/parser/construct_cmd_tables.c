/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_cmd_tables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:06:15 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 17:21:25 by rbasyrov         ###   ########.fr       */
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

int	construct_cmd_table(t_tkn_tbl *tkn_tbl, t_shell *shell, int i, int j)
{
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = &(shell->cmd_tbls[j]);
	cmd_tbl->max_n_args = 4;
	cmd_tbl->in = -1;
	cmd_tbl->out = -1;
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

// int	find_last_in_file_index(t_tkn_tbl *tkn_tbl, int i)
// {
// 	int	ind;

// 	ind = -1;
// 	while (i != tkn_tbl->n_tkns)
// 	{
// 		if (tkn_tbl->tkns[i].type == FT_PIPE)
// 			return (ind);
// 		if (tkn_tbl->tkns[i].type == FT_LESS
// 			|| tkn_tbl->tkns[i].type == FT_DLESS)
// 			ind = i;
// 		i++;
// 	}
// 	return (ind);
// }

// int	find_last_out_file_index(t_tkn_tbl *tkn_tbl, int i)
// {
// 	int	ind;

// 	ind = -1;
// 	while (i != tkn_tbl->n_tkns)
// 	{
// 		if (tkn_tbl->tkns[i].type == FT_PIPE)
// 			return (ind);
// 		if (tkn_tbl->tkns[i].type == FT_GREAT
// 			|| tkn_tbl->tkns[i].type == FT_DGREAT)
// 			ind = i;
// 		i++;
// 	}
// 	return (ind);
// }

// char	*make_tmp_heredoc_pathname(t_shell *shell, int j)
// {
// 	char	*pathname;
// 	char	*file_id;

// 	file_id = ft_itoa(j);
// 	if (file_id == NULL)
// 		clean_exit(shell, TRUE);
// 	pathname = ft_strjoin("/tmp/tmp_heredoc_", file_id);
// 	free(file_id);
// 	if (pathname == NULL)
// 		clean_exit(shell, TRUE);
// 	return (pathname);
// }

// char	*find_last_in_file(t_shell *shell, t_tkn_tbl *tkn_tbl, int i, int j)
// {
// 	char	*file;
// 	int		ind;

// 	file = NULL;
// 	ind = find_last_in_file_index(tkn_tbl, i);
// 	if (ind < 0)
// 		return (NULL);
// 	if (tkn_tbl->tkns[ind].type == FT_LESS)
// 		return (tkn_tbl->tkns[ind + 1].cntnt);
// 	else if (tkn_tbl->tkns[ind].type == FT_DLESS)
// 		return (make_tmp_heredoc_pathname(shell, j));
// 	else
// 		return (NULL);
// }

// char	*find_last_out_file(t_tkn_tbl *tkn_tbl, int i, int j)
// {
// 	char	*file;
// 	int		ind;

// 	file = NULL;
// 	ind = find_last_out_file_index(tkn_tbl, i);
// 	if (ind < 0)
// 		return (NULL);
// 	else
// 		return (tkn_tbl->tkns[ind + 1].cntnt);
// }