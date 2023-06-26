/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_environment_identifier.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:30:10 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 16:43:28 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_char_or_underscore(char c)
{
	if (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| c == '_')
		return (TRUE);
	else
		return (FALSE);
}

int	is_valid_identifier(char *cmd, char *s)
{
	int	i;

	i = 0;
	if (is_char_or_underscore(s[0]) == FALSE)
		return (FALSE);
	else
		i++;
	while (s[i] != '\0')
	{
		if (ft_strcmp(cmd, "export") == 0 && s[i] == '=')
			return (TRUE);
		if ((is_char_or_underscore(s[i]) == TRUE)
			|| ('0' <= s[i] && s[i] <= '9'))
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

void	write_identifier_error_message(char *cmd, char *s)
{
	ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
