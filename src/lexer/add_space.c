/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:31:28 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/26 14:37:36 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	to_skip_ft_space(t_tkn_tbl *tkn_tbl, const char *inp,
	int i, int ret)
{
	if (tkn_tbl->n_tkns == 0)
		return (TRUE);
	else if (tkn_tbl->tkns[tkn_tbl->n_tkns - 1].type == FT_PIPE
		|| tkn_tbl->tkns[tkn_tbl->n_tkns - 1].type == FT_GREAT
		|| tkn_tbl->tkns[tkn_tbl->n_tkns - 1].type == FT_DGREAT
		|| tkn_tbl->tkns[tkn_tbl->n_tkns - 1].type == FT_LESS
		|| tkn_tbl->tkns[tkn_tbl->n_tkns - 1].type == FT_DLESS)
		return (TRUE);
	else if (ft_strchr("<>|", inp[i + ret]) != NULL)
		return (TRUE);
	return (FALSE);
}

//add FT_SPACE only if it used to separate FT_WORD, FT_QUOTE and FT_DQUOTE
int	add_space(t_tkn_tbl *tkn_tbl, const char *inp, int i)
{
	int		ret;

	ret = 0;
	while (inp[i + ret] != '\0'
		&& ft_strchr(SPACES, inp[i + ret]) != NULL)
		ret++;
	if (to_skip_ft_space(tkn_tbl, inp, i, ret) == FALSE)
	{
		tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_SPACE;
		tkn_tbl->n_tkns += 1;
	}
	return (ret);
}
