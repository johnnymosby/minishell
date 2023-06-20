/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imitate_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:30:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/20 15:31:04 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

int	imitate_heredoc(char *s, t_shell *shell)
{
	char	*input;

	g_status = 1;
	while (TRUE)
	{
		input = readline("> ");
		if (g_status == 130)
		{
			g_status = 1;
			return (FALSE);
		}
		if (input == NULL)
			return (TRUE);
		else if (ft_strcmp(input, s) == 0)
			return (free(input), TRUE);
		free(input);
	}
	return (TRUE);
}

int	imitate_heredocs(t_tkn_tbl *tkn_tbl, int i, int last_heredoc_ind,
	t_shell *shell)
{
	while (i != tkn_tbl->n_tkns && tkn_tbl->tkns[i].type != FT_PIPE)
	{
		if (tkn_tbl->tkns[i].type == FT_DLESS && i != last_heredoc_ind)
		{
			if (imitate_heredoc(tkn_tbl->tkns[i + 1].cntnt, shell) == FALSE)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
