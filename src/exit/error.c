/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:45:02 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/21 11:04:46 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	write_file_error_message(const char *pathname)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	print_error_and_exit(t_shell *shell)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	clean_exit(shell, FT_ERROR);
}

char	*translate_enum(int n)
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
	else if (n == FT_SPACE)
		return ("FT_SPACE");
	else if (n == FT_WORD)
		return ("FT_WORD");
	else
		return ("not token");
}

void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell != NULL && shell->tkn_tbl != NULL)
	{
		while (i != shell->tkn_tbl->n_tkns)
		{
			printf("%s\n", translate_enum(shell->tkn_tbl->tkns[i].type));
			i++;
		}
	}
}

void	print_contents(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell != NULL && shell->tkn_tbl != NULL
		&& shell->tkn_tbl->tkns != NULL)
	{
		while (i != shell->tkn_tbl->n_tkns)
		{
			if (shell->tkn_tbl->tkns[i].cntnt != NULL)
				printf("%s\n", shell->tkn_tbl->tkns[i].cntnt);
			i++;
		}
	}
}
