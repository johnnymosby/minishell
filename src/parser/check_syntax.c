/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:54:18 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 14:52:25 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_syntax_error(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDOUT_FILENO);
	if (error[0] != '\0')
	{
		ft_putstr_fd("'", STDOUT_FILENO);
		ft_putstr_fd(error, STDOUT_FILENO);
		ft_putstr_fd("'", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	handle_redirection(t_tkn_tbl *tkn_tbl, int *i)
{
	if (*i + 1 == tkn_tbl->n_tkns)
		return (print_syntax_error("newline"), FALSE);
	else if (tkn_tbl->tkns[*i + 1].type != FT_WORD)
		return (print_syntax_error(tkn_type_to_str(tkn_tbl->tkns[*i].type)),
			FALSE);
	else
	{
		*i += 2;
		return (TRUE);
	}
}

int	handle_pipe(t_tkn_tbl *tkn_tbl, int *i)
{
	if (*i == 0)
		return (print_syntax_error("|"), FALSE);
	else if (*i + 1 == tkn_tbl->n_tkns)
		return (print_syntax_error("newline"), FALSE);
	else if (tkn_tbl->tkns[*i + 1].type == FT_PIPE)
		return (print_syntax_error("|"), FALSE);
	else
	{
		*i += 1;
		return (TRUE);
	}
}

void	skip_words(t_tkn_tbl *tkn_tbl, int *i)
{
	while (*i != tkn_tbl->n_tkns && tkn_tbl->tkns[*i].type == FT_WORD)
		*i += 1;
}

int	check_syntax(t_tkn_tbl *tkn_tbl, t_shell *shell)
{
	int	*i;
	int	ii;

	ii = 0;
	i = &ii;
	while (*i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[*i].type == FT_PIPE)
		{
			if (handle_pipe(tkn_tbl, i) == FALSE)
				return (set_exit_code(shell, 2), FALSE);
		}
		else if (tkn_tbl->tkns[*i].type == FT_WORD)
			skip_words(tkn_tbl, i);
		else if (if_redirection(tkn_tbl->tkns[*i].type) == TRUE)
		{
			if (handle_redirection(tkn_tbl, i) == FALSE)
				return (set_exit_code(shell, 2), FALSE);
		}
		else
			return (set_exit_code(shell, 1), FALSE);
	}
	return (TRUE);
}
