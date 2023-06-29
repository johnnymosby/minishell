/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:11:38 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/29 18:24:49 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_value()

void	expand_variables(char *s, int fd, t_shell *shell)
{
	int		i;
	int		j;
	char	*env_value;

	if (ft_strchr(s, '$') == NULL)
		return ;
	i = 0;
	while (s[i + j] != '\0')
	{
		j = 0;
		while (s[i + j] != '$')
			j++;
		write(fd, s, j - 1);
		if ('0' <= s[i + j + 1] && s[i + j + 1] <= '9')
			i += j + 1;
		else if ()
	}
	
}
