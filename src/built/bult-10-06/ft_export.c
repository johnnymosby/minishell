/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:25:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/11 18:42:43 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"
/*
Export without options: this function creates a new variable
*/
int ft_export(t_shell *cmd, char **args)
{
	int p;
	int i;

	if (nb_of_rows(args) >= 1)
	{
		i = 0;
		while (args[i])
		{
			p = is_in_envs(args[i], cmd->envs);
			if(p >= 0)
			{
				free(cmd->envs[p]);
				cmd->envs[p] = ft_strdup(args[i]);
			}
			else
				cmd->envs = ft_add_line(cmd->envs, args[i]);
			i++;
		}
	}
	return (0);
}
