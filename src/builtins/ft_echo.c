/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:59:34 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/26 18:08:49 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_repeatedn(char *s)
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

	if (ss == NULL || ss[0] == NULL)
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	i = 0;
	end = 1;
	if (is_repeatedn(ss[0]))
	{
		end = 0;
		i++;
	}
	while (ss[i] && !is_repeatedn(ss[i]))
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
