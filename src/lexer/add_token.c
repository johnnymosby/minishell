/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:33:57 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/26 14:31:43 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_pipe(t_tkn_tbl *tkn_tbl)
{
	tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_PIPE;
	tkn_tbl->n_tkns += 1;
	return (1);
}

int	add_great(t_tkn_tbl *tkn_tbl, const char *inp, int i)
{
	if (inp[i + 1] != '>')
	{
		tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_GREAT;
		tkn_tbl->n_tkns += 1;
		return (1);
	}
	else
	{
		tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_DGREAT;
		tkn_tbl->n_tkns += 1;
		return (2);
	}
}

int	add_less(t_tkn_tbl *tkn_tbl, const char *inp, int i)
{
	if (inp[i + 1] != '<')
	{
		tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_LESS;
		tkn_tbl->n_tkns += 1;
		return (1);
	}
	else
	{
		tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_DLESS;
		tkn_tbl->n_tkns += 1;
		return (2);
	}
}

int	add_word(t_tkn_tbl *tkn_tbl, const char *inp, int i, t_shell *shell)
{
	int	len;
	int	ret;

	len = 0;
	while (inp[i + len] != '\0'
		&& ft_strchr(SPACES, inp[i + len]) == NULL
		&& ft_strchr("|><\"'", inp[i + len]) == NULL)
		len++;
	ret = len;
	tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt = ft_calloc(len + 1, sizeof(char));
	if (tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt == NULL)
		clean_exit(shell);
	tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt[len] = '\0';
	while (--len >= 0)
		tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt[len] = inp[i + len];
	tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_WORD;
	tkn_tbl->n_tkns += 1;
	return (ret);
}
