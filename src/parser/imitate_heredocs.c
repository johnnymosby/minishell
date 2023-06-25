/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imitate_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:30:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 14:49:28 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	imitate_heredoc(char *s, t_shell *shell)
{
	char	*input;

	while (TRUE)
	{
		g_status = HEREDOC;
		input = readline("> ");
		if (g_status == NOCMD_SIG || g_status == CMD_SIG)
			return (FALSE);
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
