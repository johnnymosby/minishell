/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:26:33 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/09 16:50:53 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

int	find_last_heredoc_in_cmd(t_tkn_tbl *tkn_tbl, int i)
{
	int	last_heredoc_ind;

	last_heredoc_ind = -1;
	while (i != tkn_tbl->n_tkns && tkn_tbl->tkns[i].type != FT_PIPE)
	{
		if (tkn_tbl->tkns[i].type == FT_DLESS)
			last_heredoc_ind = i;
		i++;
	}
	return (last_heredoc_ind);
}

int	skip_cmd(t_tkn_tbl *tkn_tbl, int i)
{
	while (i != tkn_tbl->n_tkns && tkn_tbl->tkns[i].type != FT_PIPE)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
			return (i + 1);
		i++;
	}
	return (i);
}

void	imitate_heredoc(char *s, t_shell *shell)
{
	char	*input;

	g_status = 1;
	while (TRUE)
	{
		input = readline("> ");
		if (g_status == 130)
		{
			g_status = 1;
			return ;
		}
		if (input == NULL)
		{
			return ;
		}
		else if (ft_strcmp(input, s) == 0)
		{
			free(input);
			return ;
		}
		free(input);
	}
}

void	imitate_heredocs(t_tkn_tbl *tkn_tbl, int i, int last_heredoc_ind,
	t_shell *shell)
{
	while (i != tkn_tbl->n_tkns && tkn_tbl->tkns[i].type != FT_PIPE)
	{
		if (tkn_tbl->tkns[i].type == FT_DLESS && i != last_heredoc_ind)
			imitate_heredoc(tkn_tbl->tkns[i + 1].cntnt, shell);
		i++;
	}
}

void	handle_heredocs(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls, t_shell *shell)
{
	int	i;
	int	last_heredoc_ind;

	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
		{
			i++;
			continue ;
		}
		last_heredoc_ind = find_last_heredoc_in_cmd(tkn_tbl, i);
		if (last_heredoc_ind != -1)
			imitate_heredocs(tkn_tbl, i, last_heredoc_ind, shell);
		i = skip_cmd(tkn_tbl, i);
	}
}
