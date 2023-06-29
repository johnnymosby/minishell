/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:11:38 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/30 00:24:10 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	write_expanded_value(char *s, int fd, t_shell *shell)
{
	int	var_len;
	int	i;

	var_len = find_len_var(s);
	i = 0;
	while (shell->envs[i] != NULL)
	{
		if (ft_strncmp(shell->envs[i], s, var_len) == 0
			&& shell->envs[i][var_len] == '=')
			break ;
		i++;
	}
	if (shell->envs[i] != NULL)
		write(fd, shell->envs[i] + var_len + 1,
			ft_strlen(shell->envs[i] + var_len + 1));
	return (var_len);
}

void	expand_variables(char *s, int fd, t_shell *shell)
{
	int		i;
	int		j;
	char	*env_value;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i + j] != '\0' && s[i + j] != '$')
			j++;
		write(fd, s + i, j);
		if (s[i + j] == '\0')
			return ;
		if ('0' <= s[i + j + 1] && s[i + j + 1] <= '9')
			i += j + 2;
		else if (s[i + j + 1] == '?')
		{
			ft_putnbr_fd(shell->exit_code, fd);
			i += j + 2;
		}
		else if (s[i + j + 1] == '\0')
			i += j + write(fd, "$", 1);
		else
			i += j + write_expanded_value(s + i + j + 1, fd, shell) + 1;
	}
}
