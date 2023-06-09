/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:39:57 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/09 15:21:30 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_file_error(char *pathname)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static int	check_file(char *pathname, t_type tkn_type)
{
	if (tkn_type == FT_LESS)
	{
		if (access(pathname, R_OK) < 0)
			return (print_file_error(pathname), FALSE);
	}
	else
	{
		if (access(pathname, W_OK) < 0)
			return (print_file_error(pathname), FALSE);
	}
	return (TRUE);
}

int	check_access(t_tkn_tbl *tkn_tbl, t_shell *shell)
{
	int		i;
	t_type	type;

	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		type = tkn_tbl->tkns[i].type;
		if (type == FT_WORD || type == FT_PIPE || type == FT_QUOTE
			|| type == FT_DQUOTE)
			i++;
		else
		{
			if (i + 1 == tkn_tbl->n_tkns
				|| tkn_tbl->tkns[i + 1].type != FT_WORD)
				return (printf("minishell: redir is not followed by a word"),
					FALSE);
			if (tkn_tbl->tkns[i].type == FT_DLESS)
				i += 2;
			else if (check_file(tkn_tbl->tkns[i + 1].cntnt, type) == FALSE)
				return (FALSE);
			else
				i += 2;
		}
	}
	return (TRUE);
}
