/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:53 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/24 10:36:55 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_quote(t_tkn_tbl *tkn_tbl, const char *inp, int i, t_shell *shell)
{
	int	len;
	int	ret;

	len = 0;
	while (inp[i + len + 1] != '\0' && inp[i + len + 1] != '\'')
		len++;
	if (len == 0)
		return (1 + inp[i + len + 1] == '\0');
	tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt = ft_calloc(len + 1, sizeof(char));
	if (tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt == NULL)
		clean_exit(shell);
	tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt[len] = '\0';
	ret = len;
	while (--len >= 0)
		tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt[len] = inp[i + len];
	tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_QUOTE;
	tkn_tbl->n_tkns += 1;
	if (inp[i + ret + 1] == '\0')
		return (ret + 1);
	else
		return (ret + 2);
}

int	add_dquote(t_tkn_tbl *tkn_tbl, const char *inp, int i, t_shell *shell)
{
	int	len;
	int	ret;

	len = 0;
	while (inp[i + len + 1] != '\0' && inp[i + len + 1] != '"')
		len++;
	if (len == 0)
		return (1 + inp[i + len + 1] == '"');
	ret = len;
	tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt = ft_calloc(len + 1, sizeof(char));
	if (tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt == NULL)
		clean_exit(shell);
	tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt[len] = '\0';
	while (--len >= 0)
		tkn_tbl->tkns[tkn_tbl->n_tkns].cntnt[len] = inp[i + len];
	tkn_tbl->tkns[tkn_tbl->n_tkns].type = FT_DQUOTE;
	tkn_tbl->n_tkns += 1;
	if (inp[i + ret + 1] == '\0')
		return (ret + 1);
	else
		return (ret + 2);
}

int	add_token(t_shell *shell, int i)
{
	if (shell->trimmed_input[i] == '|')
		return (add_pipe(shell->tkn_tbl));
	else if (shell->trimmed_input[i] == '>')
		return (add_great(shell->tkn_tbl, shell->trimmed_input, i));
	else if (shell->trimmed_input[i] == '<')
		return (add_less(shell->tkn_tbl, shell->trimmed_input, i));
	else if (shell->trimmed_input[i] == '\'')
		return (add_quote(shell->tkn_tbl, shell->trimmed_input, i, shell));
	else if (shell->trimmed_input[i] == '"')
		return (add_dquote(shell->tkn_tbl, shell->trimmed_input, i, shell));
	else if (ft_strchr(SPACES, shell->trimmed_input[i]) != NULL)
		return (add_space(shell->tkn_tbl, shell->trimmed_input, i));
	else
		return (add_word(shell->tkn_tbl, shell->trimmed_input, i, shell));
	return (0);
}

void	lexer_loop(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->trimmed_input[i] != '\0')
	{
		if (shell->tkn_tbl->max_n_tkns == shell->tkn_tbl->n_tkns)
			increase_tkn_tbl(shell);
		i += add_token(shell, i);
	}
}

int	lexer(t_shell *shell)
{
	if (shell->trimmed_input[0] == '\0')
		return (FALSE);
	init_tkn_tbl(shell);
	lexer_loop(shell);
	return (TRUE);
}
