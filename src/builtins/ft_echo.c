/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:59:34 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/23 23:54:35 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_repeatedn(char *s)
{
	int	i;

	if (ft_strncmp(s, "-n", 2))
		return (0);
	i = 2;
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(char **ss)
{
	int	i;
	int	end;

	i = 0;
	end = 1;
	if (is_repeatedn(ss[0]))
	{
		end = 0;
		i++;
	}
	while (ss[i])
	{
		ft_putstr_fd(ss[i], STDOUT_FILENO);
		if (ss[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (end == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
