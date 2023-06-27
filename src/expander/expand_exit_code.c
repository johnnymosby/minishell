/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:57:17 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/27 16:50:52 by rbasyrov         ###   ########.fr       */
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
		return (free(value), write_failed_message("ft_substr"),
			clean_exit(shell, FT_ERROR));
	left_and_value = ft_strjoin(left, value);
	free(left);
	free(value);
	if (left_and_value == NULL)
		return (write_failed_message("ft_strjoin"), clean_exit(shell, 1));
	right = ft_substr(tkn->cntnt, ind + find_len_var(tkn->cntnt + ind + 1) + 2,
			ft_strlen(tkn->cntnt));
	if (right == NULL)
		return (free(left_and_value), clean_exit(shell, FT_ERROR));
	full = ft_strjoin(left_and_value, right);
	free(left_and_value);
	free(right);
	if (full == NULL)
		return (write_failed_message("ft_strjoin"), clean_exit(shell, 1));
	free(tkn->cntnt);
	tkn->cntnt = full;
}

int	expand_exit_code(int ind, t_tkn *tkn, t_shell *shell)
{
	char	*value;
	int		len_val;

	value = ft_itoa(shell->exit_code);
	if (value == NULL)
		return (write_failed_message("ft_itoa"), clean_exit(shell, FT_ERROR),
			FALSE);
	len_val = (int)ft_strlen(value);
	change_dollar_with_value(value, ind, tkn, shell);
	return (len_val);
}

int	skip_dollar_number(char *s)
{
	int	i;

	i = 0;
	while (s[i + 2] != '\0')
	{
		s[i] = s[i + 2];
		i++;
	}
	s[i] = '\0';
	return (2);
}
