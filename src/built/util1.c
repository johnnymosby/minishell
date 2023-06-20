/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:52:49 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 18:20:22 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"

int	error_message(char *name_of_func, char *mess)
{
	ft_putendl_fd(mess, STDERR_FILENO);
	return (2);
}

int	nb_of_rows(char **ss)
{
	int	i;

	i = 0;
	if (!ss)
		return (0);
	while (ss[i])
		i++;
	return (i);
}

void	n_lines_free(char **ss, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (!ss[i])
			free(ss[i]);
	}
	if (!ss)
		free(ss);
}
