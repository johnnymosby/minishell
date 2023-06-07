/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:34:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/07 12:44:12 by rbasyrov         ###   ########.fr       */
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

void	free_str_array(char ***args, int n_args)
{
	char	**arr;
	int		i;

	arr = *args;
	i = 0;
	while (i != n_args)
	{
		if (args[i] != NULL)
			free(args[i]);
		i++;
	}
	free_if_not_null((void **)args);
}

void	free_redirs(t_redir *redirs)
{
	while (redirs != NULL)
	{
		free_if_not_null((void **)redirs->file);
		redirs == redirs->next;
	}
}

void	free_cmd_tbl(t_cmd_tbl *cmd_tbl)
{
	int		i;

	i = 0;
	free_if_not_null((void **)&cmd_tbl->cmd);
	free_str_array(&cmd_tbl->args, cmd_tbl->n_args);
	free_redirs(cmd_tbl->redirs);
}

void	free_cmd_tbls(t_cmd_tbl **cmd_tbls)
{
	int		i;

	if (cmd_tbls != NULL && *cmd_tbls != NULL)
	{
		i = 0;
		while (i != (*cmd_tbls)->n_args)
		{
			free_cmd_tbl(cmd_tbls[i]);
			i++;
		}
	}
	free_if_not_null((void **)cmd_tbls);
}

void	clean_exit(t_shell *shell, int if_error)
{
	free_cmd_tbls(&shell->cmd_tbls);
	free_tkn_tbl(&shell->tkn_tbl);
	free_if_not_null((void **)&shell->prompt);
	free_input(shell);
	if (shell->if_history_exists == TRUE)
		rl_clear_history();
	free(shell);
	exit (if_error);
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

void	exit_if_true(t_shell *shell, int if_true, int if_error)
{
	print_tokens(shell);
	print_contents(shell);
	if (if_true == TRUE)
		clean_exit(shell, if_error);
}
