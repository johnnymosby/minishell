/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:19:40 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 23:41:39 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_env_variable(t_shell *shell, int i)
{
	free(shell->envs[i]);
	while (shell->envs[i] != NULL)
	{
		shell->envs[i] = shell->envs[i + 1];
		i++;
	}
}

static int	is_char_or_underscore(char c)
{
	if (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| c == '_')
		return (TRUE);
	else
		return (FALSE);
}

static int	is_valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (is_char_or_underscore(s[0]) == FALSE)
		return (FALSE);
	else
		i++;
	while (s[i] != '\0')
	{
		if ((is_char_or_underscore(s[i]) == TRUE)
			|| ('0' <= s[i] && s[i] <= '9'))
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

static void	write_identifier_error_message(char *s)
{
	ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/*
Unset without options
*/
int	ft_unset(t_shell *shell, char **args)
{
	int		i;
	int		index;

	if (!args || !args[0] || !shell->envs)
		return (0);
	i = 0;
	while (args[i] != NULL)
	{
		if (is_valid_identifier(args[i]) == FALSE)
		{
			write_identifier_error_message(args[i]);
			i++;
			continue ;
		}
		index = return_env_var_index(args[i], shell->envs);
		if (index < 0)
		{
			i++;
			continue ;
		}
		remove_env_variable(shell, index);
		i++;
	}
	return (0);
}
