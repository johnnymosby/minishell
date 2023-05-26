/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:34:38 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/26 13:44:43 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_str_and_exit(char *to_free, t_shell *shell)
{
	free(to_free);
	clean_exit(shell);
}

void	put_value(char *value, int ind, t_tkn *tkn, t_shell *shell)
{
	char	*left;
	char	*right;
	char	*left_and_value;
	char	*full;

	left = ft_substr(tkn->cntnt, 0, ind);
	if (left == NULL)
		free_str_and_exit(value, shell);
	left_and_value = ft_strjoin(left, value);
	free(left);
	free(value);
	if (left_and_value == NULL)
		clean_exit(shell);
	right = ft_substr(tkn->cntnt, ind + find_len_var(tkn->cntnt + ind + 1) + 1,
			ft_strlen(tkn->cntnt));
	if (right == NULL)
		free_str_and_exit(left_and_value, shell);
	full = ft_strjoin(left_and_value, right);
	free(left_and_value);
	free(right);
	if (full == NULL)
		clean_exit(shell);
	free(tkn->cntnt);
	tkn->cntnt = full;
}
