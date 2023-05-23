/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/23 16:22:06 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tkn_tbl(t_tkn_tbl **tkn_tbl)
{
	int		i;
	t_tkn	**tkns;
	int		n_tkns;

	if (*tkn_tbl != NULL && (*tkn_tbl)->tkns != NULL)
	{
		i = 0;
		tkns = &((*tkn_tbl)->tkns);
		n_tkns = (*tkn_tbl)->n_tkns;
		while (i != n_tkns)
		{
			free_if_not_null((void **)&(tkns[0][i].cntnt));
			i++;
		}
		free_if_not_null((void **)tkns);
	}
	free_if_not_null((void **)tkn_tbl);
}

void	clean_exit(t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_code;
	free_tkn_tbl(&shell->tkn_tbl);
	free_if_not_null((void **)&shell->trimmed_input);
	free_if_not_null((void **)&shell->prompt);
	if (shell->if_history_exists == TRUE)
		rl_clear_history();
	free(shell);
	exit (exit_code);
}

static char	*translate_enum(int n)
{
	if (n == FT_PIPE)
		return ("FT_PIPE");
	else if (n == FT_GREAT)
		return ("FT_GREAT");
	else if (n == FT_DGREAT)
		return ("FT_DGREAT");
	else if (n == FT_LESS)
		return ("FT_LESS");
	else if (n == FT_DLESS)
		return ("FT_DLESS");
	else if (n == FT_QUOTE)
		return ("FT_QUOTE");
	else if (n == FT_DQUOTE)
		return ("FT_DQUOTE");
	else if (n == FT_WORD)
		return ("FT_WORD");
	else
		return ("not token");
}

static void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (i != shell->tkn_tbl->n_tkns)
	{
		printf("%s\n", translate_enum(shell->tkn_tbl->tkns[i].type));
		i++;
	}
}

void	exit_if_true(t_shell *shell, int if_true)
{
	if (shell != NULL && shell->tkn_tbl != NULL)
		print_tokens(shell);
	if (if_true == TRUE)
		clean_exit(shell);
}
