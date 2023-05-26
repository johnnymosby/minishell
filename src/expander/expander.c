/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:19:31 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/26 13:52:10 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_env_value(char **envs, char *var, int len, t_shell *shell)
{
	int		i;
	char	*value;

	i = 0;
	while (envs[i] != NULL)
	{
		if (ft_strncmp(envs[i], var, len) == 0)
		{
			value = ft_substr(envs[i], len + 1, ft_strlen(envs[i]));
			if (value == NULL)
			{
				free(var);
				clean_exit(shell);
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}

static void	expand_variable(int ind, t_tkn *tkn, t_shell *shell)
{
	char	*var;
	int		len_var;
	char	*value;

	len_var = find_len_var(tkn->cntnt + ind + 1);
	var = ft_substr(tkn->cntnt, ind + 1, len_var);
	if (var == NULL)
		clean_exit(shell);
	value = find_env_value(shell->envs, var, len_var, shell);
	free(var);
	if (value == NULL)
		cut_out_variable(tkn->cntnt, ind);
	else
		put_value(value, ind, tkn, shell);
}

static void	expand_tkn(t_tkn *tkn, t_shell *shell)
{
	int	i;

	i = 0;
	remove_repeating_dollars(tkn->cntnt);
	remove_trailing_dollar(tkn->cntnt);
	while (tkn->cntnt[i] != '\0')
	{
		if (tkn->cntnt[i] == '$')
		{
			expand_variable(i, tkn, shell);
			i = -1;
		}
		i++;
	}
}

static void	expand_tkn_tbl(t_shell *shell, t_tkn_tbl *tkn_tbl)
{
	int		i;
	t_tkn	*tkn;

	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		tkn = &tkn_tbl->tkns[i];
		if ((tkn->type == FT_DQUOTE || tkn->type == FT_WORD)
			&& ft_strchr(tkn->cntnt, '$') != NULL)
			expand_tkn(tkn, shell);
		i++;
	}
}

int	expander(t_shell *shell)
{
	if (1)
		expand_tkn_tbl(shell, shell->tkn_tbl);
	return (TRUE);
}
