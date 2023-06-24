/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:49:00 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/24 23:51:33 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	shift_array_by_one_to_left(t_tkn_tbl *tkn_tbl, int i)
{
	while (i + 1 != tkn_tbl->n_tkns)
	{
		tkn_tbl->tkns[i].cntnt = tkn_tbl->tkns[i + 1].cntnt;
		tkn_tbl->tkns[i].type = tkn_tbl->tkns[i + 1].type;
		i++;
	}
	tkn_tbl->tkns[i].cntnt = NULL;
	tkn_tbl->tkns[i].type = 0;
}

static void	concatenate_two_words(t_tkn_tbl *tkn_tbl, int i, t_shell *shell)
{
	char	*result;

	result = ft_strjoin(tkn_tbl->tkns[i].cntnt, tkn_tbl->tkns[i + 1].cntnt);
	if (result == NULL)
	{
		ft_putstr_fd("miinishell: ft_strjoin failed with concatenate_two_words\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	free(tkn_tbl->tkns[i].cntnt);
	free(tkn_tbl->tkns[i + 1].cntnt);
	tkn_tbl->tkns[i].cntnt = result;
	tkn_tbl->tkns[i].type = FT_WORD;
	shift_array_by_one_to_left(tkn_tbl, i + 1);
	tkn_tbl->n_tkns -= 1;
}

void	concatenate_words(t_tkn_tbl *tkn_tbl, t_shell *shell)
{
	int	i;

	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		if (!(tkn_tbl->tkns[i].type == FT_WORD
				|| tkn_tbl->tkns[i].type == FT_SPACE))
			i++;
		else if (tkn_tbl->tkns[i].type == FT_WORD && (i + 1) != tkn_tbl->n_tkns
			&& tkn_tbl->tkns[i + 1].type == FT_WORD)
			concatenate_two_words(tkn_tbl, i, shell);
		else
			i++;
	}
}
