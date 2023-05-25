/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:19:31 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/25 20:48:35 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_len_var(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '$')
		i++;
	return (i);
}

char	*find_env_value(char **envs, char *var, int len, t_shell *shell)
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
}

void	put_value(char *value, int ind, t_tkn *tkn, t_shell *shell)
{
	char	*left;
	char	*right;
	char	*left_and_value;
	char	*full;

	left = ft_substr(tkn->cntnt, 0, ind);
	if (left == NULL)
	{
		free(value);
		clean_exit(shell);
	}
	left_and_value = ft_strjoin(left, value);
	free(left);
	free(value);
	if (left_and_value == NULL)
		clean_exit(shell);
	right = ft_substr(tkn->cntnt, ind + find_len_var(tkn->cntnt + ind + 1) + 1, ft_strlen(tkn->cntnt));
	if (right == NULL)
	{
		free(left_and_value);
		clean_exit(shell);
	}
	full = ft_strjoin(left_and_value, right);
	free(left_and_value);
	free(right);
	if (full == NULL)
		clean_exit(shell);
	free(tkn->cntnt);
	tkn->cntnt = full;
}

void	expand_variable(int ind, t_tkn *tkn, t_shell *shell)
{
	char	*var;
	int		len_var;
	char	*value;

	len_var = find_len_var(tkn->cntnt + 1);
	var = ft_substr(tkn->cntnt, ind + 1, len_var);
	if (var == NULL)
		clean_exit(shell);
	value = find_env_value(shell->envs, var, len_var, shell);
	free(var);
	put_value(value, ind, tkn, shell);
}

void	expand_tkn(t_tkn *tkn, t_shell *shell)
{
	int	i;

	i = 0;
	while (tkn->cntnt[i] != '\0')
	{
		if (tkn->cntnt[i] == '$')
			while (tkn->cntnt[i + 1] == '$')
				i++;
		if (tkn->cntnt[i] == '$')
			expand_variable(i, tkn, shell);
		i++;
	}
}

void	expand_tkn_tbl(t_shell *shell, t_tkn_tbl *tkn_tbl)
{
	int		i;
	t_tkn	*tkn;

	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		tkn = &tkn_tbl->tkns[i];
		if (tkn->type == FT_DQUOTE || tkn->type == FT_WORD)
			expand_tkn(tkn, shell);
		i++;
	}
}

int	expander(t_shell *shell)
{
	printf("before expand\n");
	if (1)
		expand_tkn_tbl(shell, shell->tkn_tbl);
	printf("after expand\n");
	return (TRUE);
}
