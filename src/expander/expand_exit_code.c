/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:57:17 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 00:04:05 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	change_dollar_with_value(char *value, int ind, t_tkn *tkn,
	t_shell *shell)
{
	char	*left;
	char	*right;
	char	*left_and_value;
	char	*full;

	left = ft_substr(tkn->cntnt, 0, ind);
	if (left == NULL)
	{
		free(value);
		ft_putstr_fd("minishell: ft_substr failed in expander\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	left_and_value = ft_strjoin(left, value);
	free(left);
	free(value);
	if (left_and_value == NULL)
	{
		ft_putstr_fd("minishell: ft_strjoin failed in expander\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	right = ft_substr(tkn->cntnt, ind + find_len_var(tkn->cntnt + ind + 1) + 2,
			ft_strlen(tkn->cntnt));
	if (right == NULL)
		return (free(left_and_value), clean_exit(shell, FT_ERROR));
	full = ft_strjoin(left_and_value, right);
	free(left_and_value);
	free(right);
	if (full == NULL)
	{
		ft_putstr_fd("minishell: ft_strjoin failed in expander\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	free(tkn->cntnt);
	tkn->cntnt = full;
}

int	expand_exit_code(int ind, t_tkn *tkn, t_shell *shell)
{
	char	*value;
	int		len_val;

	value = ft_itoa(shell->exit_code);
	if (value == NULL)
	{
		ft_putstr_fd("minishell: ft_itoa failed in expand_exit_code\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	len_val = (int)ft_strlen(value);
	change_dollar_with_value(value, ind, tkn, shell);
	return (len_val);
}
