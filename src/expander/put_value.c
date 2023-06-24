/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:38 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 00:01:16 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		ft_putstr_fd("minishell: ft_substr failed in put_value\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	left_and_value = ft_strjoin(left, value);
	free(left);
	if (left_and_value == NULL)
	{
		ft_putstr_fd("minishell: ft_strjoin failed in put_value\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	right = ft_substr(tkn->cntnt, ind + find_len_var(tkn->cntnt + ind + 1) + 1,
			ft_strlen(tkn->cntnt));
	if (right == NULL)
		return (free(left_and_value), clean_exit(shell, FT_ERROR));
	full = ft_strjoin(left_and_value, right);
	free(left_and_value);
	free(right);
	if (full == NULL)
	{
		ft_putstr_fd("minishell: ft_strjoin failed in put_value\n", STDERR_FILENO);
		clean_exit(shell, FT_ERROR);
	}
	free(tkn->cntnt);
	tkn->cntnt = full;
}
