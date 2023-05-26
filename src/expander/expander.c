/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:19:31 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/26 13:02:31 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cut_out_variable(char *s, int ind)
{
	int	j;

	j = 0;
	while (s[j] != '\0')
		j++;
	if (j <= ind || s[ind] != '$')
		return ;
	j = ind;
	ind++;
	while (s[ind] != '\0' && s[ind] != '$')
		ind++;
	while (s[ind] != '\0')
	{
		s[j] = s[ind];
		ind++;
		j++;
	}
	s[j] = '\0';
}

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
	return (NULL);
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

void	remove_repeating_dollars(char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (!(s[i] == '$' && s[i + 1] == '$'))
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
}

void	remove_trailing_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (i > 0 && s[i - 1] == '$')
		s[i - 1] = '\0';
}

void	expand_tkn(t_tkn *tkn, t_shell *shell)
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

void	expand_tkn_tbl(t_shell *shell, t_tkn_tbl *tkn_tbl)
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
