/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:19:40 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 12:17:16 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"

/*
Unset without options
*/
int	ft_unset(t_shell *cmd, char **args)
{
	char	*tmp;
	int		a[2];

	a[0] = 0;
	if (nb_of_rows(args) >= 1)
	{
		while (args[++a[0]])
		{
			if (args[a[0]][ft_strlen(args[a[0]]) - 1] != '=')
			{
				tmp = ft_strjoin(args[a[0]], "=");
				free(args[a[0]]);
				args[a[0]] = tmp;
			}
			a[1] = is_in_envsv(args[a[0]], cmd->envs);
			if (a[1] >= 0)
				ft_remove_line(cmd->envs, NULL, a[1]);
		}
	}
	return (0);
}
